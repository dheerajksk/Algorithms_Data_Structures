#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

void partition3(vector<int> &a, int l, int r, int &m1, int &m2) {
  int x = a[l];
  m1 = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] < x) {
      m1++;
      swap(a[i], a[m1]);
    }
  }
  swap(a[l], a[m1]);
  m2 = m1;
  for (int i = m1 + 1; i <= r; i++) {
    if (a[i] == x) {
      m2++;
      swap(a[i], a[m2]);
    }
  }
  //return 0;
}

void randomized_quick_sort_part3(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  //std::cout << "In ran sort " << l << " " << r << std::endl;

  int k = l + rand() % (r - l + 1);
  int m1, m2;
  swap(a[l], a[k]);
  partition3(a, l, r, m1, m2);

  randomized_quick_sort_part3(a, l, m1 - 1);
  randomized_quick_sort_part3(a, m2 + 1, r);
}

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  int m = partition2(a, l, r);

  randomized_quick_sort(a, l, m - 1);
  randomized_quick_sort(a, m + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort_part3(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
