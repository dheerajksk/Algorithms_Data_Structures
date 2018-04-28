#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

long long hash_func(const string& s) {
        static const long long multiplier = 263;
        static const long long prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash;
}

/*size_t *precompute_hash(const Data& input){
  static const size_t multiplier = 263;
  static const size_t prime = 1000000007;
  const string& s = input.pattern, t = input.text;
  int P = static_cast<int> (s.size());
  int T = static_cast<int> (t.size());
  string t_sub = t.substr(T-P, T-1);
  size_t ans[T-P+1];
  ans[T-P] = hash_func(t_sub);
  size_t y = 1;
  for(int i = 0; i < P; i++) y = ( y * multiplier ) % prime ;
  for(int i = T - P - 1; i>=0; --i)  ans[i] = (multiplier*ans[i+1] + t[i] - y * t[i+P]) % prime ;
  return &ans;
}*/

std::vector<int> RabinKarp(const Data& input) {
  const string& s = input.pattern, t = input.text;
  std::vector<int> ans;
  if (s.size() == t.size()) {
    if (t == s) ans.push_back(0);
    return ans;
  }
  static const long long multiplier = 263;
  static const long long prime = 1000000007;
  int P = static_cast<int> (s.size());
  int T = static_cast<int> (t.size());
  //std::cout << P << T << std::endl;
  string t_sub = t.substr(T-P, T-1);
  //std::cout << t_sub << std::endl;
  long long pHash = hash_func(s);
  //std::cout << "phash: " << pHash << std::endl;
  long long hash[T-P+1];
  hash[T-P] = hash_func(t_sub);
  long long y = 1;
  long long temp;
  for(int i = 1; i <= P; i++) {temp = ( y * multiplier ) ; y = (( temp % prime) + prime) % prime;}
  for(int i = T - P - 1; i>=0; i--) { temp = (multiplier*hash[i+1] + t[i] - y * t[i+P]); hash[i] = (( temp % prime) + prime) % prime ;}
  //for(int i = 0; i < T-P+1; i++) std::cout << i << ":" << hash[i] << " check: " << hash_func(t.substr(i, s.size())) << std::endl;

  for(int i = 0; i < T-P+1; i++){
    if (pHash != hash[i]) {
      //std::cout << pHash << " " << hash[i] << std::endl;
      continue;
    }
    //std::cout << t.substr(i, s.size()) << "::" << s << std::endl;
    if (t.substr(i, s.size()) == s){
      //std::cout << pHash << " " << hash[i] << std::endl;
      ans.push_back(i);
    }
  }
  return ans;
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(RabinKarp(read_input()));
    return 0;
}
