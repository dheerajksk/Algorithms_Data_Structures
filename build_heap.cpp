#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;
  int minIndex_ ;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void SiftDown(){
    int currMinIndex = minIndex_ ;
    int l = 2*currMinIndex + 1;
    if( l <= (data_.size() - 1) && data_[l] < data_[minIndex_])
      minIndex_ = l;
    int r = 2*currMinIndex + 2;
    if( r <= (data_.size() - 1) && data_[r] < data_[minIndex_])
      minIndex_ = r;
    //std::cout << "l: " << l << " r:" << r << " currIndex: "  << currMinIndex << " minIndex: " << minIndex_ << std::endl;
    if (currMinIndex != minIndex_){
      swap(data_[currMinIndex], data_[minIndex_]);
      swaps_.push_back(make_pair(currMinIndex, minIndex_));
      SiftDown();
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    for (int i = data_.size(); i >=0; --i){
      minIndex_ = i;
      //std::cout << minIndex_ << std::endl;
      SiftDown();
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
