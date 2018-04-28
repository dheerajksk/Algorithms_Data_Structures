#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  long int key;
  long int left;
  long int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(long int key_, long int left_, long int right_) : key(key_), left(left_), right(right_) {}
};

bool in_order_traversal(const vector <Node> & tree, int index, long int &prev, long int &prev_index, bool &is_bst_bool) {
  bool write_output = false;
  if (write_output) cout << "new launch: index=" << index << "prev key=" << " " << prev << "prev index= " << prev_index << "\n" ;
  if (tree[index].left > -1) { 
    in_order_traversal(tree, tree[index].left, prev, prev_index, is_bst_bool);
    if(write_output) cout << "launched left: curr_index= " << index << "left_index= " << tree[index].left << "prev= " << prev << " prev index= " << prev_index << "\n" ;
  } 
  if (prev < tree[index].key) {
    if(write_output) cout << "less than: prev key= " << prev << "curr_key=" << tree[index].key << "\n"; 
    prev = tree[index].key;
    prev_index = index; }
  else if( prev == tree[index].key ) {
    if(write_output) cout << "equal\n"; 
    if(write_output) cout << "prev_index =" << prev_index << "prev_index_left= " << tree[prev_index].left << " prev_index_right= " << tree[prev_index].right << "\n" ;
    if(write_output) cout << "pre_key =" << tree[prev_index].key << " leftt_key=" << tree[tree[prev_index].left].key << " right_key=" << tree[tree[prev_index].right].key << "\n" ; 
    if (tree[prev_index].left == -1 && tree[prev_index].right > -1){
      if (tree[prev_index].key <= tree[tree[prev_index].right].key){
        prev = tree[index].key;
        prev_index = index; 
        }
      else is_bst_bool=false;
    }
    else if (tree[prev_index].left > -1 && tree[prev_index].right == -1){
      if (tree[prev_index].key > tree[tree[prev_index].left].key){
        prev = tree[index].key;
        prev_index = index; 
        }
      else is_bst_bool=false;
    }
    else {
      if ( tree[prev_index].key > tree[tree[prev_index].left].key && tree[prev_index].key <= tree[tree[prev_index].right].key ){
        prev = tree[index].key;
        prev_index = index; 
        }
      else is_bst_bool=false;
    }
  }
  else is_bst_bool = false;
  if (tree[index].right > -1) {
    in_order_traversal(tree, tree[index].right, prev, prev_index, is_bst_bool);
    if(write_output) cout << "launched right: curr_index=" << index << "right_index= " << tree[index].right << " prev_key=" << prev << " prev_index=" << prev_index << "\n" ;
    }
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  long int prev = LONG_MIN;
  long int prev_index = 0;
  bool is_bst_bool = true;
  in_order_traversal(tree, 0, prev, prev_index, is_bst_bool);
  return is_bst_bool;
}

int main() {
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 256 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    long int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (nodes == 0)
    cout << "CORRECT" << endl;
  else{
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  }
  return 0;
}
