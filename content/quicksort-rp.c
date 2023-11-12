#include <stdlib.h>

void quicksort(int a[], int n) {
  if( n < 2 ) return;
  
  int pivot_idx = n < 3 ? 0 : rand() % n;
  
  int right = n-1;
  int left = 0;
  int pivot = a[pivot_idx];
  a[pivot_idx] = a[right];
  
  // Put all elements smaller than pivot to the left (lower part)
  // and all larger elements to the right.
  while( left < right ) {
    if( a[left] <= pivot ) {
      left++;
    } else {
      a[right] = a[left];
      right--;
      a[left] = a[right];
    }
  }
  a[right] = pivot;
  // All elements to the left of 'right' are now smaller than 
  // all elements to the right (above) 'right'.
  
  quicksort(a, right); // Sort the smaller elements
  quicksort(a + right + 1, n - right - 1); // Sort the larger elements
}
