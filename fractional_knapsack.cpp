#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstdlib>
using std::vector;

double get_optimal_value(double capacity, vector<double> weights, vector<double> values) {
  double value = 0.0;
  double density, A;
  int n = weights.size();
  int index = -1;
  double cap_double = capacity;
  //std::cout << cap_double << std::endl;
  //while (cap_double > 1.0e-04) {
  for (int j = 0; j < n ; j++) {
    //std::cout << "Capacity: " << cap_double << std::endl;
    density = 0.0;
    index = -1;
    for (int i=0; i < n; i++){
      if (weights[i] > 1.0e-04){
        if (density <  values[i]/weights[i]){
          density = values[i]/weights[i];
          index = i;
        }
      }
    }
      //std::cout << "index: " << index << std::endl;
      if (index != -1) {
        A = fmin(weights[index], cap_double);
      //if (A > 1.0e-04){
      value = value +  A*values[index]/weights[index] ;
      weights[index] = weights[index] - A;
      cap_double = cap_double - A;
      }
      //std::cout << "index:" << index << " capacity:" << cap_double << " value:" << value << std::endl;
  }


  // write your code here

  return value;
}

int main() {
  int n;
  double capacity;
  std::cin >> n >> capacity;
  vector<double> values(n);
  vector<double> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  //std::cout.precision(10);
  std::cout << std::setprecision(9) << optimal_value << std::endl;
  return 0;
}
