#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct {
   double val;
   size_t index;
} nonzero_t;

// Sparse dot product calculation
double ip(nonzero_t *sv, size_t n_nonzero, double* dv) {
  double sum = 0;
  for(size_t i = 0; i < n_nonzero; i++) {
    sum += sv[i].val * dv[sv[i].index];
  }
  return sum;
}

// Traditional dot product calculation
double traditional_ip(double *v1, double *v2, size_t size) {
  double sum = 0;
  for(size_t i = 0; i < size; i++) {
    sum += v1[i] * v2[i];
  }
  return sum;
}

// Generate a random dense vector
void generate_dense_vector(double *vector, size_t size, double sparsity) {
  for(size_t i = 0; i < size; i++) {
    // Generate random values between -10 and 10
    vector[i] = (double)rand() / RAND_MAX * 20.0 - 10.0;

    // Apply sparsity (for creating sparse vectors)
    if ((double)rand() / RAND_MAX < sparsity) {
      vector[i] = 0.0;
    }
  }
}

// Convert a dense vector to sparse representation
size_t dense_to_sparse(double *dense, size_t size, nonzero_t **sparse) {
  // Count non-zero elements
  size_t count = 0;
  for(size_t i = 0; i < size; i++) {
    if(dense[i] != 0.0) {
      count++;
    }
  }

  // Allocate sparse vector
  *sparse = (nonzero_t*)malloc(count * sizeof(nonzero_t));
  if(*sparse == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  // Fill sparse vector
  size_t j = 0;
  for(size_t i = 0; i < size; i++) {
    if(dense[i] != 0.0) {
      (*sparse)[j].val = dense[i];
      (*sparse)[j].index = i;
      j++;
    }
  }

  return count;
}

// Print vectors for verification
void print_vectors(double *v1, double *v2, size_t size, nonzero_t *sparse, size_t n_nonzero) {
  printf("Dense vector 1:\n");
  for(size_t i = 0; i < size; i++) {
    printf("%.2f ", v1[i]);
    if((i + 1) % 10 == 0) printf("\n");
  }
  printf("\n\n");

  printf("Dense vector 2:\n");
  for(size_t i = 0; i < size; i++) {
    printf("%.2f ", v2[i]);
    if((i + 1) % 10 == 0) printf("\n");
  }
  printf("\n\n");

  printf("Sparse representation of vector 1:\n");
  for(size_t i = 0; i < n_nonzero; i++) {
    printf("index: %zu, value: %.2f\n", sparse[i].index, sparse[i].val);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  // Default values
  size_t size = 1000;
  char method[10] = "both";
  double sparsity = 0.9; // 90% of elements will be zero

  // Parse command-line arguments
  for(int i = 1; i < argc; i++) {
    if(strcmp(argv[i], "--size") == 0 && i + 1 < argc) {
      size = atoi(argv[i + 1]);
      i++;
    } else if(strcmp(argv[i], "--method") == 0 && i + 1 < argc) {
      strcpy(method, argv[i + 1]);
      i++;
    } else if(strcmp(argv[i], "--sparsity") == 0 && i + 1 < argc) {
      sparsity = atof(argv[i + 1]);
      i++;
    } else if(strcmp(argv[i], "--help") == 0) {
      printf("Usage: %s [--size N] [--method METHOD] [--sparsity S]\n", argv[0]);
      printf("  --size N        Size of vectors (default: 1000)\n");
      printf("  --method METHOD Method to use: 'sparse', 'traditional', or 'both' (default: both)\n");
      printf("  --sparsity S    Sparsity level between 0 and 1 (default: 0.9)\n");
      printf("  --help          Show this help message\n");
      return 0;
    }
  }

  // Seed random number generator
  srand(time(NULL));

  // Allocate memory for dense vectors
  double *v1 = (double*)malloc(size * sizeof(double));
  double *v2 = (double*)malloc(size * sizeof(double));

  if(v1 == NULL || v2 == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return EXIT_FAILURE;
  }

  // Generate random vectors
  generate_dense_vector(v1, size, sparsity);
  generate_dense_vector(v2, size, 0.0); // Second vector is fully dense

  // Convert first vector to sparse representation
  nonzero_t *sparse_v1;
  size_t n_nonzero = dense_to_sparse(v1, size, &sparse_v1);

  printf("Vector size: %zu\n", size);
  printf("Number of non-zero elements in sparse vector: %zu (%.2f%%)\n",
         n_nonzero, (double)n_nonzero / size * 100);

  // Print small vectors for verification (only if size is manageable)
  if(size <= 100) {
    print_vectors(v1, v2, size, sparse_v1, n_nonzero);
  }

  // Calculate dot product using specified method
  double result_sparse, result_traditional;
  clock_t start, end;
  double cpu_time_sparse = 0, cpu_time_traditional = 0;

  if(strcmp(method, "sparse") == 0 || strcmp(method, "both") == 0) {
    start = clock();
    result_sparse = ip(sparse_v1, n_nonzero, v2);
    end = clock();
    cpu_time_sparse = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Sparse method result: %.6f (time: %.6f seconds)\n", result_sparse, cpu_time_sparse);
  }

  if(strcmp(method, "traditional") == 0 || strcmp(method, "both") == 0) {
    start = clock();
    result_traditional = traditional_ip(v1, v2, size);
    end = clock();
    cpu_time_traditional = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Traditional method result: %.6f (time: %.6f seconds)\n", result_traditional, cpu_time_traditional);
  }

  // Compare results if both methods were used
  if(strcmp(method, "both") == 0) {
    printf("\nComparison:\n");
    printf("Absolute difference: %.10f\n", fabs(result_sparse - result_traditional));
    printf("Speedup ratio: %.2fx\n", cpu_time_traditional / cpu_time_sparse);
  }

  // Free allocated memory
  free(v1);
  free(v2);
  free(sparse_v1);

  return 0;
}