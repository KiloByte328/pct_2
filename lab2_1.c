#include <stdio.h>
#include <mpi.h>
#include <math.h>

double func (double x)
{
    return x*x*x*x / (((x*x) / 2) + x + 6);
}

int main (int argc, char* argv[])
{
    MPI_Init (&argc, &argv);
    int rank, commsize;
    double eps = 1E-6;
    double n = 100;
    double a = 0.4;
    double b = 1.5;
    double h = (b - a) / n;
    double new_sum = 0.0;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double diff = 0.0;
    double start = MPI_Wtime();
    for (int presc = 1; diff < eps; presc++)
    {
        double sum = 0.0;
        int my_left = presc * ((n / commsize) * rank);
        int my_right = (rank != commsize - 1) ? ((presc * (n / commsize) * (rank + 1)) - 1) : (n * presc - 1);
        for (int i = my_left; i <= my_right; i++)
        {
            sum += func(a + (h / 2) * i);
        }
        MPI_Allreduce(&sum, &new_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        new_sum = new_sum * h;
        diff = new_sum - diff;
    }
    double end = MPI_Wtime() - start;
    if (rank == 0)
        printf("Result is: %f\n clculated in %f\n", new_sum, end);
    MPI_Finalize();
    return 0;
}