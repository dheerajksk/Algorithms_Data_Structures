#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

void printQueue(std::queue <Node> node_q){
  std::queue <Node> showq = node_q;
  while(!showq.empty()){
    Node currNode = showq.front();
    std::cout << "\t" << currNode.key ;
    showq.pop();
  }
  std::cout << "\n" ;
}

int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;
  int root_index;

  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else
      root_index = child_index;
    nodes[child_index].key = child_index;
  }

  // Replace this code with a faster implementation
  /*int maxHeight = 0;
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    maxHeight = std::max(maxHeight, height);
  }
    
  std::cout << maxHeight << std::endl;*/

  std::queue <Node> node_q;

  int maxHeight = 0;

  node_q.push(nodes[root_index]);
  while(!node_q.empty()){
    int node_count = node_q.size();
    maxHeight++;
    while(node_count > 0){
      Node currNode = node_q.front();
      node_q.pop();
      int numchildren = currNode.children.size();
      for(int child_index=0; child_index < numchildren; child_index++){
      //if (nodes[currNode.children[child_index]->key].children.size() > 0)
        node_q.push(nodes[currNode.children[child_index]->key]);
      //maxHeight--;
      }
      node_count = node_count - 1;
    }
  }

  std::cout << maxHeight << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
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
  return main_with_large_stack_space();
}
