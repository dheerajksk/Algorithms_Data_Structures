#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost, int nedges) {
  vector <int> dist(adj.size(), 10000000);
  vector <int> prev;
  dist[0] = 0;
  int iter = 0;

  for(int i = 0; i < adj.size(); i++){
    for(int u = 0; u < adj.size(); u++){
      for(int iadj = 0; iadj < adj[u].size(); iadj++){
        int v = adj[u][iadj];
        int w_vu = cost[u][iadj];
        //iter = iter + 1;
        if(dist[v] > dist[u] + w_vu){
          dist[v] = dist[u] + w_vu;
          prev.push_back(v+1);
          if(i==adj.size()-1) iter = 1;
        }
      }
    }
  }

  //std::cout << (adj.size())*nedges << " " << prev.size() << " " << iter << std::endl;
  if(iter < 1) return 0;
  else return 1;
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
  std::cout << negative_cycle(adj, cost, m);
}
