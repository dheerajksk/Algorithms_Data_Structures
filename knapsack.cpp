#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w) {
  //int value[w.size()+1][W+1];
  int val = 0;
  vector< vector <int> > value;
  value.resize( w.size()+1, vector <int>( W+1, val ));
  //for(size_t j=0; j<=W; j++)
  //  for(size_t i=0; i<= w.size(); i++)
  //    value[i][j]=0;

  for(size_t i=1; i<=w.size(); i++){
    for(size_t j=1; j<=W; j++){
      value[i][j] = value[i-1][j];
      if (w[i-1] <= j){
        val = value[i-1][j-w[i-1]] + w[i-1];
        if (value[i][j] <  val) value[i][j] = val;
      }
    }
  }
  //write your code here
//  int current_weight = 0;
//  for (size_t i = 0; i < w.size(); ++i) {
//    if (current_weight + w[i] <= W) {
//      current_weight += w[i];
//    }
//  }
    /*for(size_t i=0; i<= w.size(); i++){
      for(size_t j=0; j<=W; j++) std::cout << value[i][j] << " " ;
      std::cout << std::endl;
    }*/
  return value[w.size()][W];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
