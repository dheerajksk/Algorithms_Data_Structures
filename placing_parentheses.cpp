#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>

using std::vector;
using std::string;
using std::max;
using std::min;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

long long get_maximum_value(const string &exp) {
  int explen = exp.length();
  int n = (explen + 1) / 2 ;
  int d[n];
  int val_min[n][n], val_max[n][n];
  for(size_t i=0; i< n; i++)
    for(size_t j=0; j< n; j++){
    val_min[i][j] = 0;
    val_max[i][j] = 0;
    }

  for(size_t i =0; i<n; i++){
    string str = &exp[2*i];
    int int_d;
    sscanf(str.c_str(), "%d", &int_d);
    val_min[i][i] = int_d;
    val_max[i][i] = int_d;
    d[i] = int_d;
    std::cout << d[i] << std::endl;
    }

  for(size_t s=1; s < n; s++){
    for(size_t i = 0; i < n-s; i++){
    size_t j = i + s;
    long long loc_min = LONG_MAX;
    long long loc_max = LONG_MIN;
    std::cout << "i,j: " << i << " " << j << std::endl;
    for(size_t k = i; k<=j-1; k++){
      char op = exp[2*k+1];
      long long a = eval(val_max[i][k], val_max[k+1][j], op);
      long long b = eval(val_max[i][k], val_min[k+1][j], op);
      long long c = eval(val_min[i][k], val_max[k+1][j], op);
      long long d1 = eval(val_min[i][k], val_min[k+1][j], op);
      loc_min = min({a,b,c,d1,loc_min});
      loc_max = max({a,b,c,d1,loc_max});
      std::cout << "k=" << k << " op=|" << op << "| a=" << a << " b=" << b << " c=" << c << " d=" << d1 << std::endl;
    }
    val_min[i][j] = loc_min;
    val_max[i][j] = loc_max;
  }
  }

  for(size_t i=0; i< n; i++){
    for(size_t j=0; j< n; j++) std::cout << val_min[i][j] << " ";
    std::cout << std::endl;
    }
  
  std::cout << "======MAX========" << std::endl;

  for(size_t i=0; i< n; i++){
    for(size_t j=0; j< n; j++) std::cout << val_max[i][j] << " ";
    std::cout << std::endl;
    }


  //write your code here
  return val_max[0][n-1];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
  return 0;
}
