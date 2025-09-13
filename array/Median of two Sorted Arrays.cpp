/*
https://leetcode.com/problems/median-of-two-sorted-arrays/description/?envType=problem-list-v2&envId=array
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

 

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

*/

//https://www.geeksforgeeks.org/dsa/median-of-two-sorted-arrays-of-different-sizes/

// C++ Program to find the median of two sorted arrays
// of different size using Binary Search

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

double medianOf2(vector<int> &a, vector<int> &b) {
    int n = a.size(), m = b.size();
	
  	// If a[] has more elements, then call medianOf2 
  	// with reversed parameters
    if (n > m)
        return medianOf2(b, a);
  
    int lo = 0, hi = n;
    while (lo <= hi) {
        int mid1 = (lo + hi) / 2;
        int mid2 = (n + m + 1) / 2 - mid1;

        // Find elements to the left and right of partition in a[]
        int l1 = (mid1 == 0 ? INT_MIN : a[mid1 - 1]);
        int r1 = (mid1 == n ? INT_MAX : a[mid1]);

        // Find elements to the left and right of partition in b[]
        int l2 = (mid2 == 0 ? INT_MIN : b[mid2 - 1]);
        int r2 = (mid2 == m ? INT_MAX : b[mid2]);

        // If it is a valid partition
        if (l1 <= r2 && l2 <= r1) {
          
          	// If the total elements are even, then median is 
          	// the average of two middle elements
            if ((n + m) % 2 == 0)
                return (max(l1, l2) + min(r1, r2)) / 2.0;
          
          	// If the total elements are odd, then median is 
         	// the middle element
            else
                return max(l1, l2);
        }

        // Check if we need to take lesser elements from a[]
        if (l1 > r2)
            hi = mid1 - 1;
      
        // Check if we need to take more elements from a[]
        else
            lo = mid1 + 1;
    }
    return 0;
}

int main() {
    vector<int> a = {1, 12, 15, 26, 38};
    vector<int> b = {2, 13, 17, 30, 45, 60};
  
    cout << medianOf2(a, b);
    return 0;
}

Time Complexity: O(log(min(m, n))), since binary search is applied on the smaller array.
Auxiliary Space: O(1)
//

double findMedianSortedArrays(const std::vector<int>& A,
                              const std::vector<int>& B) {
    const std::vector<int>& X = (A.size() <= B.size()) ? A : B;
    const std::vector<int>& Y = (A.size() <= B.size()) ? B : A;
    int m = X.size(), n = Y.size();

    int lo = 0, hi = m;
    while (lo <= hi) {
        int i = (lo + hi) / 2;
        int j = (m + n + 1) / 2 - i;

        int L1 = (i == 0) ? INT_MIN : X[i - 1];
        int R1 = (i == m) ? INT_MAX : X[i];
        int L2 = (j == 0) ? INT_MIN : Y[j - 1];
        int R2 = (j == n) ? INT_MAX : Y[j];

        if (L1 <= R2 && L2 <= R1) {                         // perfect cut
            if ((m + n) & 1) return std::max(L1, L2);       // odd length
            return (std::max(L1, L2) + std::min(R1, R2)) / 2.0;
        }
        else if (L1 > R2)
            hi = i - 1;                                     // move i left
        else
            lo = i + 1;                                     // move i right
    }
    return 0.0;                                             // unreachable
}
