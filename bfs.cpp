#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  vector <int> dist(adj.size(), 1000000);
  queue <int> vertex_q;
  dist[s] = 0;
  vertex_q.push(s);
  while(!vertex_q.empty()){
    int currVertex = vertex_q.front();
    vertex_q.pop();
    for(int i = 0; i < adj[currVertex].size(); i++){
      if(dist[adj[currVertex][i]] == 1000000){
        vertex_q.push(adj[currVertex][i]);
        dist[adj[currVertex][i]] = dist[currVertex] + 1;
      }
    }
  }
  if(dist[t] < 1000000) return dist[t];
  else return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
