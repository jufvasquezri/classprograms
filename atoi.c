// gcc -lgsl -lgslcblas 
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_linalg.h>

void init(double Adata[], double bdata[], const int n);
void solve(const int n);

int
main (int argc, char **argv)
{
  srand48(0);

  const int N = atoi(argv[1]); // Repetitions
  const int M = atoi(argv[2]); // Matrix size


  int step;
  for (step = 0; step < N; ++step) {
    solve(M);
  }


  return 0;
}


void init(double Adata[], double bdata[], const int n)
{
  int ii, jj;
  for (ii = 0; ii < n; ++ii) {
    bdata[ii] = drand48();      
    for (jj = 0; jj < n; ++jj) {
      Adata[ii*n + jj] = drand48();      
    }
  }
}

void solve(const int n)
{
  double *Adata, *bdata;
  Adata = malloc(n*n*sizeof(double));
  bdata = malloc(n*sizeof(double));

  init(Adata, bdata, n);

  gsl_matrix_view m = gsl_matrix_view_array (Adata, n, n);
  gsl_vector_view b = gsl_vector_view_array (bdata, n);
  gsl_vector *x = gsl_vector_alloc (n);
  gsl_vector *tau = gsl_vector_alloc (n); // for QR
  int s;

  // decomposition
  gsl_linalg_QR_decomp (&m.matrix, tau);
  gsl_linalg_QR_solve (&m.matrix, tau, &b.vector, x);

  //printing
  printf ("x = \n");
  gsl_vector_fprintf (stdout, x, "%g");

  // resource release 
  gsl_vector_free (tau);
  gsl_vector_free (x);

  free(Adata);
  free(bdata);

}

