#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;
using std::make_pair;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie_new(vector <string> & patterns){

  trie t;
  int currNode;
  int index = 1;
  edges e = {};
  t.push_back(e);

  for (size_t i = 0; i < patterns.size(); i++ ){
    currNode = 0;
    for( size_t j = 0; j < patterns[i].length(); j++){
      char str = patterns[i][j];
      //std::cout << t.size() << " " << currNode << " " << index << " " << str << std::endl;
      auto search = t[currNode].find(str);
      if (search != t[currNode].end()) {
          currNode = search-> second;
      }
      else {
        //std::cout << "Added new edge from: " << currNode << " to: " << index << " with " << str << std::endl;
        t[currNode][str] = index;
        currNode = index;
        edges e1 = {}; t.push_back(e1); 
        index = index + 1;
      }
    }
    
  }

  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie_new(patterns);

  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
