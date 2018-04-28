#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using std::vector;
using std::pair;

//void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
  //write your code here
//}     

void explore(vector< vector<int> > &adj, vector <int> &visit, vector <int> &used, vector <int> &order, int v){
  visit[v] = 1;
  //std:: cout << "visited: " << v+1 << "\n" ;
  //if (adj[v].size() == 0) order.push_back(v);
  //else {
  for(int i = 0; i < adj[v].size(); i++){
    int nextVertex = adj[v][i];
    //if (visit[nextVertex] != 1 && used[nextVertex] != 1) explore(adj, visit, used, order, nextVertex);
    if (visit[nextVertex] != 1) explore(adj, visit, used, order, nextVertex);
  }
  //}
  //used[v] = 1;
  order.push_back(v);
}

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  //write your code here
  vector<int> visited(adj.size());
  for(int i = 0; i < adj.size(); i++){
    if(visited[i] != 1) {explore(adj, visited, used, order, i);}
  }
  //dfs(adj, used, order);
  return order;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order = toposort(adj);
  for (vector <int> :: reverse_iterator i = order.rbegin(); i != order.rend(); ++i) {
    std::cout << *i + 1 << " ";
  }
}
