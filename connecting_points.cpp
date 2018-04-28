#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <cmath>

# define INF 0x3f3f3f3f

using namespace std;
using std::vector;
using std::pair;
using std::make_pair;

typedef pair<double, int> int_pair;

double minimum_distance(vector<double> x, vector<double> y) {
  double result = 0.;
  priority_queue <int_pair, vector<int_pair>, greater<int_pair> > pq;
  int src = 0;
  double dist;
  vector <double> cost(x.size(), 10000000.0);
  vector <bool> inMST(x.size(), false);
  vector <int> parent(x.size(), -1);

  cost[src] = 0.0;
  pq.push(make_pair(0.0,src));

  while(!pq.empty()){
    int u = pq.top().second;
    pq.pop();
    inMST[u] = true;

    for(int i = 0; i < x.size(); i++){
      dist = sqrt((x[u] - x[i])*(x[u] - x[i]) + (y[u] - y[i])*(y[u]-y[i]));
      //std::cout << u << " " << i << " ";
      //std::cout << std::fixed << std::showpoint;
      //std::cout << std::setprecision(8);
      //std::cout << x[u]-x[i] << " " << y[u] - y[i] << " " << dist << std::endl;

      if(inMST[i] == false && cost[i] > dist){
        cost[i] = dist;
        parent[i] = u;
        pq.push(make_pair(dist, i));
      }
    }
  }

  for(int i = 1; i < parent.size(); i++){
    dist = sqrt(pow((x[parent[i]] - x[i]),2.0) + pow((y[parent[i]] - y[i]),2.0));
    result = result + dist;
    //std::cout << i << " " << parent[i] << " " << dist << std::endl; 
  }
  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<double> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
    std::cout << std::fixed << std::showpoint;
    //std::cout << x[i] << " " << y[i] << std::endl;
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
