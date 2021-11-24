#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int numeroAleatorio();
int somaAuxiliar();

int rank, size;
double somaTot, result = 0.0;
MPI_Status st;

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            int randNum = rand() % 100 + 1;
            MPI_Send(&randNum, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else {        
        somaAuxiliar();
    }

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Recv(&result, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &st);
            somaTot += result;
        }
        printf("Soma Total no Pricipal = %f\n", somaTot);
    }
    
    MPI_Finalize();
    return 0;

}

int somaAuxiliar()
{
    int x;
    MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);

    double soma = 2.971 * exp(0.138 * x);
    printf("Soma Parcial no processo %d = %f\n", rank, soma);

    MPI_Send(&soma, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    return 1;
}