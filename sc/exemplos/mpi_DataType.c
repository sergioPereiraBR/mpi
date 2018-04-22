#include <stdio.h>
#include "mpi.h"

int main( argc, argv )
int argc;
char **argv;
{
    int          rank;
    struct { int a; double b;} value;
    MPI_Datatype mystruct;
    int          blocklens[2];
    MPI_Aint     indices[2];
    MPI_Datatype old_types[2];

    MPI_Init( &argc, &argv );

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    /* One value of each type */
    blocklens[0] = 1;
    blocklens[1] = 1;
    /* The base types */
    old_types[0] = MPI_INT;
    old_types[1] = MPI_DOUBLE;
    /* The locations of each element */
    MPI_Address( &value.a, &indices[0] );
    MPI_Address( &value.b, &indices[1] );
    /* Make relative */
    indices[1] = indices[1] - indices[0];
    indices[0] = 0;
    MPI_Type_struct( 2, blocklens, indices, old_types, &mystruct );
    MPI_Type_commit( &mystruct );

    do {
        if (rank == 0)
            scanf( "%d %lf", &value.a, &value.b );

        MPI_Bcast( &value, 1, mystruct, 0, MPI_COMM_WORLD );

        printf( "Process %d got %d and %lf ", rank, value.a, value.b );
    } while (value.a >= 0);

    /* Clean up the type */
    MPI_Type_free( &mystruct );
    MPI_Finalize( );
    return 0;
}