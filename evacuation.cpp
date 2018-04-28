#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>
//#include <array>

using std::vector;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        //std::cout << "added forward edge: " << to << " " << from << " " << capacity << " edged size: " << edges.size() << std::endl;
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
};

FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    /*std::cout << graph.size() << std::endl;
    for(size_t i = 0; i < graph.size(); i++){
      vector <size_t> edges_ids = graph.get_ids(i);
      std::cout << edges_ids.size() << std::endl;
    }*/
    return graph;
}

int max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;

    while(true){
    //for(int iter=0; iter<3; iter++){
    std::queue <int> vertex_q;
    while(!vertex_q.empty()) vertex_q.pop();
    vertex_q.push(from);
    bool match_sink = false;
    vector <size_t> edge_id_bfs;
    int parent[graph.size()] = {};
    for(int i=0; i < graph.size(); i++) parent[i] = -1;
    //parent[from] = -1;
    while(!vertex_q.empty() && match_sink == false){
      int currVertex = vertex_q.front();
      //std::cout << "currVertex: " << currVertex << std::endl ;
      vertex_q.pop();
      vector <size_t> edges_ids = graph.get_ids(currVertex);
      for(size_t i = 0; i < edges_ids.size(); i++){
        size_t currEdgeId = edges_ids[i];
        FlowGraph::Edge currEdge = graph.get_edge(currEdgeId);
        //std::cout << "curredge: " << currEdgeId << "goes from: " << currEdge.from << " to: " << currEdge.to << std::endl;
        //if(currEdge.from == currVertex && (currEdge.capacity - currEdge.flow) > 0) {
        if(parent[currEdge.to] == -1 && (currEdge.capacity - currEdge.flow) > 0) {
          if(currEdge.to == currEdge.from) continue;
          edge_id_bfs.push_back(currEdgeId);
          parent[currEdge.to] = currVertex;
          if(currEdge.to == to){ match_sink = true; break;}
          vertex_q.push(currEdge.to);
          }
      }
    }

    if(match_sink == false) break;
    //else std::cout << "path exists\n" ;

    bool source_found = false;
    int min_flow = INT_MAX;
    for(int v = to; v != from; v = parent[v]){
      int u = parent[v];
      //std::cout << "parent of: " << v << " is: " << u << std::endl;
      vector<size_t> edges_ids = graph.get_ids(u);
      for(size_t i = 0; i < edges_ids.size(); i++){
        size_t currEdgeId = edges_ids[i];
        FlowGraph::Edge currEdge = graph.get_edge(currEdgeId);
        if(currEdge.from == u && currEdge.to == v){
          if(currEdge.flow < currEdge.capacity) {min_flow = std::min(min_flow, (currEdge.capacity-currEdge.flow)); break;}
          //std::cout << "edge from: " << u << " to: " << v << std::endl;
        }
      }
    }

    //std::cout << "min_flow: " << min_flow << std::endl;
    flow = flow + min_flow;
    
    for(int v = to; v != from; v = parent[v]){
      int u = parent[v];
      vector<size_t> edges_ids = graph.get_ids(u);
      for(size_t i = 0; i < edges_ids.size(); i++){
        size_t currEdgeId = edges_ids[i];
        FlowGraph::Edge currEdge = graph.get_edge(currEdgeId);
        if(currEdge.from == u && currEdge.to == v){
          //std::cout << "edge: " << currEdgeId << " from: " << u << " to: " << v << "flow updated" << std::endl;
          //std::cout << "flow before: " << currEdge.flow << std::endl;
          if(currEdge.flow < currEdge.capacity) {graph.add_flow(currEdgeId, min_flow); break;}
          //FlowGraph::Edge newEdge = graph.get_edge(currEdgeId);
          //std::cout << "flow after: " << newEdge.flow << std::endl;
        }
      }
    }

    }//overall loop while(true)
    /* your code goes here */
    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
