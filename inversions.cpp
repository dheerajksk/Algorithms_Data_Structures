#include <iostream>
#include <vector>

using std::vector;

int merge(vector<int> &a, vector<int> &b, size_t left, size_t ave, size_t right){
  size_t i = left;
  size_t j = ave;
  size_t count = 0;
  for(size_t k = left; k < right; k++){
    if (i < ave && ( j >= right || a[i] <= a[j])){
      b[k] = a[i];
      i=i+1;
      }
    else {
      b[k] = a[j];
      j = j+1;
      count = count + 1;
      }
  }
  
  for(size_t index = left; index < right; index++) a[index]=b[index];

  return count;
}

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
  long long number_of_inversions = 0;
  if (right <= left + 1) return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  std::cout << left << ave << right << number_of_inversions <<std::endl;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  std::cout << left << ave << right << number_of_inversions <<std::endl;
  number_of_inversions += get_number_of_inversions(a, b, ave+1, right);
  number_of_inversions += merge(a,b,left,ave,right);
  //write your code here
  return number_of_inversions;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  //std::cout <<"========="<<std::endl;
  std::cout << get_number_of_inversions(a, b, 0, a.size()-1) << '\n';
  //std::cout <<"========="<<std::endl;
  //for (size_t i = 0; i < a.size(); i++) {
  //  std::cout << b[i] << std::endl;
 // }
}
