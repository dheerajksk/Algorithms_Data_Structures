#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(vector< vector<int> > &adj, vector <int> &visit, int v, vector <int> &pre, vector <int> &post, int &clock){
  visit[v] = 1;
  pre[v] = clock;
  clock = clock + 1;
  //std:: cout << "visited: " << v+1 << "\n" ;
  for(int i = 0; i < adj[v].size(); i++){
    int nextVertex = adj[v][i];
    if (visit[nextVertex] != 1) explore(adj, visit, nextVertex, pre, post, clock);
  }
  post[v] = clock;
  clock = clock + 1;
}

int acyclic(vector<vector<int> > &adj) {
  int n = adj.size();
  vector<int> visited(n);
  vector<int> pre(n);
  vector<int> post(n);
  int cc = 0;
  int clock = 1;
  for(int i = 0; i < adj.size(); i++){
    if(visited[i] != 1) {explore(adj, visited, i, pre, post, clock); cc = cc + 1;}
  }
  //std::cout << cc << std::endl;
  int is_acyclic = 0;
  for(int i = 0; i < adj.size(); i++){
    for(int j = 0; j < adj[i].size(); j++) {
      //std::cout << i+1 << " " << adj[i][j]+1 << " " << post[i] << " " << post[adj[i][j]] << std::endl;
      if (post[i] < post[adj[i][j]]) is_acyclic = 1;
    }
  }
  return is_acyclic;
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
  std::cout << acyclic(adj);
}
