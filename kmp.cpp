#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  if (pattern.length() > text.length()) return result;

  // computePrefixFunction
  string all = pattern + '$' ;
  all += text;
  int s[all.length()];
  int border = 0;
  s[0] = 0;
  int iter = 0;

  for(size_t i = 1; i < all.length(); i++){
    while( border > 0 && all.at(i) != all.at(border)) { border = s[border-1]; iter += 1; }
    if ( all.at(i) == all.at(border) ) border = border + 1;
    else border =0;
    s[i] = border;
  }

  //cout << iter << std::endl;
  //for(size_t i=0; i < all.length(); i++) cout << s[i] << " ";
  //cout << std::endl;

  for(size_t i = pattern.length() + 1; i < all.length(); i++) {
    if (s[i] == pattern.length()) result.push_back(i - 2*pattern.length());
  } 

  // Implement this function yourself
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  if(text == pattern){
      printf("0\n");
  }
  else if(text.length() > pattern.length()){
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  }
  return 0;
}
