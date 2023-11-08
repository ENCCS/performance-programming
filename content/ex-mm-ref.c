void matmul(double* a, double* b, double* c, long n) {
  for(long i = 0; i < n; i++) {
    for(long j = 0; j < n; j++) {
      double sum = 0;
      for(long k = 0; k < n; k++) {
        sum += b[i*n + k] * c[k*n + j];
      }
      a[i*n + j] = sum;
    }
  }
}

