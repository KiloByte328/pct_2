#include <stdio.h>
#include <mpi.h>

double func (double x, double y)
{

}

int main (int argc, char* argv[])
{
    MPI_init (&argc, &argv);
    int rank, commsize;
    double eps = 1E-6;
    double h;
    double a;
    double b;
    double n = 0.01;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for(double i = a; i <= b;)
    {
        
    }
    MPI_Finalize();
    return 0;
}