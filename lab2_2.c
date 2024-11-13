#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    const double PI = 3.14159265358979323846;
    int n = 1000000;
    int all_in = 0;
    int n_all_in;
    double sum = 0.0;
    double n_sum;
    int rank, commsize;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srand(rank);
    double start = MPI_Wtime();
    for (int k = 0; k < n; k += commsize)
    {
        double x = (-1) * ((double)rand() / RAND_MAX);
        double y = (double)rand() / RAND_MAX;
        if (y <= cos(x))
        {
            all_in++;
            sum = sum + exp((x - y));
        }
    }
    MPI_Reduce(&sum, &n_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&all_in, &n_all_in, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {    
        double v = PI * n_all_in / n;
        double res = v * n_sum / n_all_in;
        double end = MPI_Wtime() - start;
        printf("result is: %f\n n is: %d\n all dots inside: %d, time of work is: %f\n", res, n, n_all_in, end);
    }
    MPI_Finalize();
    return 0;
}