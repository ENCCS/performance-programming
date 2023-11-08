#include "rtvl.h"

void matmul(double* a, double* b, double* c, long n) {
  long rn = rtvl(n);
  for(long i = 0; i < n; i++) {
    for(long j = 0; j < n; j++) a[i*rn + j] = 0;
    for(long k = 0; k < n; k++) {
      for(long j = 0; j < n; j++) {
        a[i*rn + j] += b[i*rn + k] * c[k*rn + j];
      }
    }
  }
}
