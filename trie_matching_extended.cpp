#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
  bool patternNode;

	Node ()
	{
		fill (next, next + Letters, NA);
    patternNode = false;
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}

  bool isPattern () const
  {
    return patternNode;
  }

};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

vector <int> solve (const string& t, int n, const vector <string>& patterns)
{
	vector <int> result;
  vector <Node> trie;

  Node root;
  int currNode = 0;
  int index = 1;
  trie.push_back(root);

  for(size_t i = 0; i < patterns.size(); i++){
    currNode = 0;
    for( size_t j = 0; j < patterns[i].length(); j++){
      char str = patterns[i][j];
      int letter_index = letterToIndex(str);

      if( trie[currNode].next[letter_index] != NA ){
        currNode = trie[currNode].next[letter_index];
        }
      else {
        trie[currNode].next[letter_index] = index;
        currNode = index;
        Node another;
        trie.push_back(another);
        index = index + 1;
        }
      if( j == patterns[i].length() - 1 ) 
        //{ if (!trie[currNode].isLeaf()) trie[currNode].patternNode = true; }
        { trie[currNode].patternNode = true; }
    }
  }

  for(size_t i= 0; i < t.length(); i++ ){
    index = i;
    currNode = 0;
    while (index < t.length()) {
      char c = t[index];
      int letter_index = letterToIndex(c);
      if( trie[currNode].next[letter_index] == NA ) break;
      currNode = trie[currNode].next[letter_index];
      if( trie[currNode].isPattern() ) {result.push_back(i);}
      if( trie[currNode].isLeaf() ) {result.push_back(i); break;}
      index = index + 1;
    }
  }

  sort(result.begin(), result.end());
  result.erase( unique( result.begin(), result.end()), result.end());
	return result;
}

vector<int> test(const vector<string>& patterns, const string& text){
    vector<int> pos;
    for (int i=0; i< text.size();i++){
        for (int j=0; j< patterns.size();j++){
            if ((patterns[j].size()+i-1)< text.size()){
                string sub=text.substr(i,patterns[j].size());
                if (sub.compare(patterns[j])==0){
                    pos.push_back(i);
                    break;
                }
            }
        }
    }
    sort(pos.begin(),pos.end());
    cout << "Completed Naive\n" ;
    return pos;
}

string random_string(const int len) {

    string result="";
    static const char alphanum[] =
        "ACGT";

    for (int i = 0; i < len; ++i) {
        result+= alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return result;
}
int main (void)
{

  while (false) {

    string t;
    int n = rand() % 20 + 1;

    t = random_string(n);
    cout << "Text: " << t << "\n" ;

    int n_patterns = rand() % 5 + 1;
    vector <string> patterns(n_patterns);
    cout << "Patterns: " << n_patterns << "\n" ;

    for(size_t i = 0; i < n_patterns; i++){
      int n = rand() % 5 + 1;
      string str = random_string(n);
      cout << str << "\n";
      patterns[i] = str;
    }

    for(size_t i = 0; i < n_patterns; i++){
      cout << patterns[i] << "\n" ;
    }
    
    vector <int> result;
    result = test( patterns, t);
	
    vector <int> ans;
	  ans = solve (t, n_patterns, patterns);

    if(result.size() == ans.size()){
      for(size_t i = 0; i < result.size(); i++)
        if (result[i] != ans[i]) break;
    }
    else if(result.size() != ans.size()) break;
    else cout << "success\n";

  }

	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}
  
  /*vector <int> result;
  result = test( patterns, t);
	for (int i = 0; i < (int) result.size (); i++)
	{
		cout << result[i];
		if (i + 1 < (int) result.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}*/

	vector <int> ans;
	ans = solve (t, n, patterns);
  //cout << "trie matching\n" ;

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
