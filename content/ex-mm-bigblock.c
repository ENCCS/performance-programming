#include "rtvl.h"
#include <string.h>

void matmul(double* a, double* b, double* c, long n) {
  const long rn = rtvl(n);
  const long m = n%4;
  const long jb = n > 512 ? 512 : n;
  const long kb = n < 256 ? 4 * (1024 / jb) : 16;
  for(long jj = 0; jj < n; jj += jb) {
    long jlim = jj+jb <= n ? jj+jb : n;
    for(long kk = 0; kk < n; kk += kb) {
      long klim = kk+kb <= n ? kk+kb : n;
      for(long i = 0; i < n; i+=2) {
        if(kk == 0) {
          memset(a + (i+0)*rn + jj, 0, (jlim-jj)*sizeof(double));
          memset(a + (i+1)*rn + jj, 0, (jlim-jj)*sizeof(double));
        }
        for(long k = kk; k < klim-3; k+=4) {
          double b00 = b[(i+0)*rn + k + 0];
          double b01 = b[(i+0)*rn + k + 1];
          double b02 = b[(i+0)*rn + k + 2];
          double b03 = b[(i+0)*rn + k + 3];
          double b10 = b[(i+1)*rn + k + 0];
          double b11 = b[(i+1)*rn + k + 1];
          double b12 = b[(i+1)*rn + k + 2];
          double b13 = b[(i+1)*rn + k + 3];
          #pragma omp simd
          for(long j = jj; j < jlim; j++) {
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
        if(klim == n) {
          for( long k = n-m; k < n; k++ ) {
            #pragma omp simd
            for( long j = jj; j < jlim; j++ ) {
              a[    i*rn + j] += b[    i*rn + k] * c[k*rn + j];
              a[(i+1)*rn + j] += b[(i+1)*rn + k] * c[k*rn + j];
            }
          }
        }
      }
    }
  }
}
