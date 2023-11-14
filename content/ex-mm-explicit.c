#include <malloc.h>
#include <stdlib.h>

typedef double __attribute__((vector_size(32))) v4d_t;

#define YB 4
#define XB 2
static const long yB = YB;
static const long xB = XB;

#define min(a,b) ((a) < (b) ? (a) : (b))

void matmul(double* a, double* b, double* c, long n) {
  v4d_t* va = (v4d_t*) a;
  v4d_t* vb = (v4d_t*) b;
  v4d_t* vc = (v4d_t*) c;
  _Alignas(64) v4d_t vcT[512];
  long JB =  8;
  long KB = 64;
  long IB = n <= 512 ? n : 4*KB;
    
  long KBB = IB;
  long no4 = n/4;
  double* cT = (double*) vcT;

  for(long ii = 0; ii < n; ii += IB) {
    long ilim = min(n, ii+IB);
    for(long kkk = 0; kkk < n; kkk += KBB) {
      long kklim = min(n, kkk+KBB);
      for(long jj = 0; jj < no4; jj += JB) {
        long jlim = min(no4, jj + JB);
        for(long kk = kkk; kk < kklim; kk += KB) {
          long klim = min(kklim, kk + KB);
          long koff = klim - kk;
          // Transpose part of the c matrix
          for(long k = kk; k < klim; k++) {
            for(long j = jj; j < jlim; j+=2) {
              vcT[(j-jj)*koff + k-kk] = vc[k*no4 + j];
              vcT[(j-jj+1)*koff + k-kk] = vc[k*no4 + j + 1];
            }
          }
          for(long i = ii; i < ilim; i+=xB ) {
            for(long j = jj; j < jlim; j += yB) {
              // Prefetch the part of the a matrix that we will update
              #pragma GCC unroll xB
              for(long ui = 0; ui < xB; ui++) {
                #pragma GCC unroll yB/2
                for(long uj = 0; uj < yB; uj+=2) {
                  __builtin_prefetch(va + (i+ui)*no4 + j + uj, 1);
                }
              }
              // Do the summation loop
              v4d_t sum[XB][YB] = {0};
              for(long k = kk; k < klim; k++ ) {
                #pragma GCC unroll xB
                for(long ui = 0; ui < xB; ui++) {
                  #pragma GCC unroll yB
                  for(long uj = 0; uj < yB; uj++) {
                    sum[ui][uj] += b[(i+ui)*n + k] * vcT[(j-jj+uj)*koff + k-kk];
                  }
                }
              }
              // Update the a matrix
              if(kk == 0) {
                // First k block so we have no previous sum to add to
                #pragma GCC unroll 2
                for(long ui = 0; ui < xB; ui++) {
                  #pragma GCC unroll yB
                  for(long uj = 0; uj < yB; uj++) {
                    va[(i+ui)*no4 + j + uj] = sum[ui][uj];
                  }
                }
              } else {
                // We will add the results of the k-loop to the previous partial sums
                #pragma GCC unroll 2
                for(long ui = 0; ui < xB; ui++) {
                  #pragma GCC unroll yB
                  for(long uj = 0; uj < yB; uj++) {
                    va[(i+ui)*no4 + j + uj] += sum[ui][uj];
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

