#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(vector< vector<int> > &adj, vector <int> &visit, int v){
  visit[v] = 1;
  //std:: cout << "visited: " << v+1 << "\n" ;
  for(int i = 0; i < adj[v].size(); i++){
    int nextVertex = adj[v][i];
    if (visit[nextVertex] != 1) explore(adj, visit, nextVertex);
  }
}

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  //write your code here
  int n = adj.size();
  vector<int> visited(n);
  int cc = 0;
  for(int i = 0; i < adj.size(); i++){
    if(visited[i] != 1) {explore(adj, visited, i); cc = cc + 1;}
  }
  return cc;
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
  std::cout << number_of_components(adj);
}
