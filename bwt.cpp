#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  string result = "";
  int n =  text.length();

  vector <string> rotations;

  //get rotations
  for(size_t i = 0; i < n; i++) {
    string front_prt = text.substr(i+1); //get string from pos i to end
    string back_prt = text.substr(0,i+1);
    //cout << front_prt << " " << back_prt << endl;
    //front_prt.append(back_prt,0,back_prt.length()-1);
    front_prt += back_prt;
    //cout << front_prt << endl;
    rotations.push_back(front_prt);
  }
  //cout << rotations.size() << endl;

  sort(rotations.begin(), rotations.end());

  for(size_t i=0; i < rotations.size(); i++) {
    char last = rotations[i][n-1];
    result += last;
    //cout << rotations[i] << endl;
  }

  //cout << result << endl;

  // write your code here

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
