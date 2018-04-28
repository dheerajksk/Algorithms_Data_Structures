#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int letterToIndex (char letter)
{
	switch (letter)
	{
		case '$': return 0; break;
		case 'A': return 1; break;
		case 'C': return 2; break;
		case 'G': return 3; break;
		case 'T': return 4; break;
		default: assert (false); return -1;
	}
}

string InverseBWT(const string& bwt) {
  string text = "";
  const int NE = 5;
  const int text_len = bwt.length();
  int count[NE] = {};
  int C[NE] = {};
  int C_[text_len];
  int LF[text_len] ;

  for(size_t i = 0; i < bwt.length(); i++) {
    char str = bwt.at(i);
    count[letterToIndex(str)] += 1;
  }

  C[0] = 0;

  //for(size_t i=0; i< NE; i++) { cout << count[i] << " ";}
  //cout << endl;
  for(size_t i=1; i< NE; i++) { C[i] = C[i-1] + count[i-1];}
  //for(size_t i=0; i< NE; i++) { cout << C[i] << " ";}

  for(size_t i = 0; i < bwt.length(); i++) {char str = bwt.at(i); C_[i] = C[letterToIndex(str)] ;}// cout << C_[i] << " " ;}
  for(size_t i=0; i< NE; i++) count[i] = 0;
  //cout << endl;

  for(size_t i = 0; i < bwt.length(); i++) {char str = bwt.at(i); count[letterToIndex(str)] += 1; LF[i] = count[letterToIndex(str)];}// cout << LF[i] << " " ;}
  //cout << endl;
  for(size_t i = 0; i< bwt.length(); i++)  LF[i] = LF[i] + C_[i]; //cout << LF[i] << " ";}
  //cout << endl;

  // write your code here
  int r = 1;
  char c = bwt[r-1];
  int iter = 0;
  while (c != '$' ){
    //cout << iter << " " << c << " " << text << endl;
    text += c;
    r = LF[r-1];
    c = bwt[r-1];
    iter += 1;
  }

  reverse(text.begin(), text.end());
  text += '$' ;

  return text;
}

int main() {
  string bwt ;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
