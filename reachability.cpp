#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(vector< vector<int> > &adj, vector <int> &visit, int v, int y, int &reachable){
  visit[v] = 1;
  if(v == y){reachable = 1; return;}
  //std:: cout << "visited: " << v+1 << "\n" ;
  for(int i = 0; i < adj[v].size(); i++){
    int nextVertex = adj[v][i];
    if (visit[nextVertex] != 1) explore(adj, visit, nextVertex, y, reachable);
  }
}

int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  int n = adj.size();
  vector<int> visited(n);
  int reachable = 0;
  explore(adj, visited, x, y, reachable);
  return reachable;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
