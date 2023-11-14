#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "rtvl.h"

void matmul(double* a, double* b, double* c, long n);

static int close(double a, double b) {
  return fabs(a-b) < 0.001*(fabs(a) + fabs(b));
}

int main(int argc, char** argv) {
  long n, r = 1;
  if( argc == 2 ) {
    n = atol(argv[1]);
  } else {
    r = atol(argv[1]);
    n = atol(argv[2]);
  }
  
  long rn = rtvl(n);
  
  long size = n*rn*sizeof(double);
  double* a;
  double* b;
  double* c;
  
  if(posix_memalign((void**)&a, 64, size)) exit(EXIT_FAILURE);
  if(posix_memalign((void**)&b, 64, size)) exit(EXIT_FAILURE);
  if(posix_memalign((void**)&c, 64, size)) exit(EXIT_FAILURE);
  
  for(long i = 0; i < n; i++ ) {
    for(long j = 0; j < n; j++ ) {
      c[i*rn + j] = 1.0/sqrt(i+1) + 1.0/sqrt(j+1);
      b[i*rn + j] = i == j ? 1 : 0;
    }
  }
  
  for(int m = 0; m < r; m++ ) {
    matmul(a, b, c, n);
  }
  
  int ok = 1;
  for(long i = 0; i < n; i++ ) {
    for(long j = 0; j < n; j++ ) {
      ok = ok && close(a[i*rn + j], c[i*rn + j]);
    }
  }
  
  printf( "Ok = %d\n", ok );
  
  free(a);
  free(b);
  free(c);
  
  return 0;
}


