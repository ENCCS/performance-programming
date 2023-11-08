#include "rtvl.h"
#include <string.h>

void matmul(double* a, double* b, double* c, long n) {
  long rn = rtvl(n);
  long m = n%4;
  for(long i = 0; i < n; i+=2) {
    memset(a + i*rn, 0, 2*rn*sizeof(double));
    for(long k = 0; k < n-3; k+=4) {
      double b00 = b[(i+0)*rn + k + 0];
      double b01 = b[(i+0)*rn + k + 1];
      double b02 = b[(i+0)*rn + k + 2];
      double b03 = b[(i+0)*rn + k + 3];
      double b10 = b[(i+1)*rn + k + 0];
      double b11 = b[(i+1)*rn + k + 1];
      double b12 = b[(i+1)*rn + k + 2];
      double b13 = b[(i+1)*rn + k + 3];
      #pragma omp simd
      for(long j = 0; j < n; j++) {
        double s0 = a[i*rn + j];
        double s1 = a[(i+1)*rn + j];
        s0 += b00 * c[k*rn + j];
        s1 += b10 * c[k*rn + j];
        s0 += b01 * c[(k+1)*rn + j];
        s1 += b11 * c[(k+1)*rn + j];
        s0 += b02 * c[(k+2)*rn + j];
        s1 += b12 * c[(k+2)*rn + j];
        s0 += b03 * c[(k+3)*rn + j];
        s1 += b13 * c[(k+3)*rn + j];
        a[    i*rn + j] = s0;
        a[(i+1)*rn + j] = s1;
      }
    }
    for( long k = n-m; k < n; k++ ) {
      #pragma omp simd
      for( long j = 0; j < n; j++ ) {
        a[    i*n + j] += b[    i*n + k] * c[k*n + j];
        a[(i+1)*n + j] += b[(i+1)*n + k] * c[k*n + j];
      }
    }
  }
}
