/*#include <iostream>
#include <vector>
#include <queue>*/
#include <bits/stdc++.h>
using namespace std;

/*using std::vector;
using std::queue;
using std::pair;
using std::make_pair;
using std::priority_queue;*/

typedef pair<int, int> int_pair;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  priority_queue <int_pair, vector<int_pair>, greater<int_pair> > pq;
  vector <int> dist(adj.size(), 1000000);
  dist[s] = 0;
  pq.push(make_pair(dist[s], s));
  while(!pq.empty()){
    int u = pq.top().second;
    pq.pop();
    for(int i=0; i < adj[u].size(); i++){
      int v = adj[u][i];
      int w_vu = cost[u][i];
      if (dist[v] > dist[u] + w_vu){
        dist[v] = dist[u] + w_vu;
        pq.push(make_pair(dist[v], v));
      }
    }
  }
  if (dist[t] < 1000000) return dist[t];
  else return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
