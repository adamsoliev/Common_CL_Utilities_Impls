#include "atl.h"
#include <bits/stdc++.h>
using namespace std;

void merge(vector<int> &nums, int left, int mid, int right) {
  // find sizes
  auto left_half_size = mid - left + 1;
  auto right_half_size = right - mid;

  vector<int> left_arr(nums.begin() + left, nums.begin() + mid + 1);
  vector<int> right_arr(nums.begin() + mid + 1, nums.begin() + right + 1);

  /*
  // create arr arrays
  cout << "\nNUMS: ";
  atl::printV(nums);
  cout << "left: " << left << ", mid: " << mid << ", right: " << right << endl;
  cout << "LEFT: ";
  atl::printV(left_arr);
  cout << "RIGHT: ";
  atl::printV(right_arr);

  // old way of copying
  // create arr arrays
  vector<int> left_arr(left_half_size);
  vector<int> right_arr(right_half_size);

  // copy data from nums to left & right arr arrays
  for (auto i = 0; i < left_half_size; ++i) {
    left_arr[i] = nums[left + i];
  }
  for (auto i = 0; i < right_half_size; ++i) {
    right_arr[i] = nums[mid + 1 + i];
  }
  */

  auto idx_left_arr = 0, idx_right_arr = 0;
  auto idx_merged_arr = left;
  // merge two arr array back to nums
  while (idx_left_arr < left_half_size && idx_right_arr < right_half_size) {
    if (left_arr[idx_left_arr] <= right_arr[idx_right_arr]) {
      nums[idx_merged_arr++] = left_arr[idx_left_arr++];
    } else {
      nums[idx_merged_arr++] = right_arr[idx_right_arr++];
    }
  }

  // copy remaining nums of
  // left array, if there are any
  while (idx_left_arr < left_half_size) {
    nums[idx_merged_arr++] = left_arr[idx_left_arr++];
  }
  // right array, if there are any
  while (idx_right_arr < right_half_size) {
    nums[idx_merged_arr++] = right_arr[idx_right_arr++];
  }
}

void mergeSort(vector<int> &nums, int left, int right) {
  if (left >= right)
    return;
  auto mid = left + (right - left) / 2;
  mergeSort(nums, left, mid);
  mergeSort(nums, mid + 1, right);
  merge(nums, left, mid, right);
}

int main() {
  vector<int> nums{3, 5, 1, 6, 3, 0, -3, 9, -25, 34};
  mergeSort(nums, 0, nums.size() - 1);
  atl::printV(nums);

  return 0;
}
