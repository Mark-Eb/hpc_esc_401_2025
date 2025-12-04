#include <mpi.h>
#include <stdio.h>
#include "init.h"

int start_MPI(int* my_rank, int* size){
	printf("Setting MPI environment\n");
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,size);
	MPI_Comm_rank(MPI_COMM_WORLD,my_rank);

	return 0;
}

int close_MPI(){
	MPI_Finalize();
	return 0;
}

int mpi_get_domain(int nx, int ny, int my_rank, int size,  int* min_x, int* max_x, int* min_y, int* max_y){
    /*
    sets the boundaries of the local domain for a given rank 
    */
	*min_y = 0;
	*max_y = ny; //will go up to max_y-1

	*min_x = nx/size*my_rank;
	if (my_rank == size -1)
		*max_x = nx;
	else 
		*max_x = nx/size*(my_rank+1);

	printf("I am rank %d and my domain is: xmin, xmax, ymin, ymax: %d %d %d %d\n",my_rank, *min_x, *max_x, *min_y, *max_y);
	return 0;
}

void halo_comm(params p, int my_rank, int size, double** u, 
               double* fromLeft, double* fromRight){
    /*
    provdes the column vectors to be sent to right and left (slab domain decomposition)
    */

    // Store ranks of neighbors
    p.right_rank = (my_rank + 1);
    if (p.right_rank >= size) p.right_rank = -1;
    p.left_rank = (my_rank - 1);
    p.top_rank=-1;
    p.bottom_rank=-1;
    // printf("I am rank %d, my neighbours are: left: %d, right: %d, bottom: %d, top: %d\n",my_rank,p.left_rank, p.right_rank, p.bottom_rank, p.top_rank);

    // Group for synchronous split communication
    if (my_rank%2==0)
        p.my_group=1;
    else
        p.my_group=2;


    int size_x = p.xmax-p.xmin;
    int size_y = p.ymax-p.ymin;


    /*-----------------------------------------------------*/
    /*----------manually selected columns to be sent-------*/
    /*-----------------------------------------------------*/


    // double col_to_right[size_y], col_to_left[size_y];
    // for (int j=0;j<size_y;j++) col_to_right[j] = u[size_x - 1][j];
    // for (int j=0;j<size_y;j++) col_to_left[j] = u[0][j];



    // Blocking communication strategy

	// if (p.my_group==1){
	// 	if (p.right_rank>=0) MPI_Send(col_to_right, size_y, MPI_DOUBLE, p.right_rank, 0, MPI_COMM_WORLD);
	// 	if (p.left_rank>=0)  MPI_Send(col_to_left,  size_y, MPI_DOUBLE, p.left_rank,  0, MPI_COMM_WORLD);
	// 	if (p.left_rank>=0)  MPI_Recv(fromLeft,     size_y, MPI_DOUBLE, p.left_rank,  0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
	// 	if (p.right_rank>=0) MPI_Recv(fromRight,    size_y, MPI_DOUBLE, p.right_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	// }
	// else{
	// 	if (p.left_rank>=0)  MPI_Recv(fromLeft,     size_y, MPI_DOUBLE, p.left_rank,  0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	// 	if (p.right_rank>=0) MPI_Recv(fromRight,    size_y, MPI_DOUBLE, p.right_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	// 	if (p.left_rank>=0)  MPI_Send(col_to_left,  size_y, MPI_DOUBLE, p.left_rank,  0, MPI_COMM_WORLD);		
	// 	if (p.right_rank>=0) MPI_Send(col_to_right, size_y, MPI_DOUBLE, p.right_rank, 0, MPI_COMM_WORLD);	
	// }


    /*-----------------------------------------------------*/
    /*---------------------MPI_Datatype--------------------*/
    /*-----------------------------------------------------*/


    MPI_Datatype column_type;
    int len_col=p.ymax - p.ymin, stride_col=1;
    MPI_Type_vector(len_col, 1, stride_col, MPI_DOUBLE, &column_type);
    MPI_Type_commit(&column_type);


    // Blocking communication strategy

    if (p.my_group==1){
        // issue MPI command only if valid left/right neighbour
        if (p.right_rank>=0) MPI_Send(&u[p.xmax-p.xmin-1][0], 1, column_type, p.right_rank, 0, MPI_COMM_WORLD);
        if (p.left_rank>=0)  MPI_Send(&u[0][0], 1, column_type, p.left_rank,  0, MPI_COMM_WORLD);
        if (p.left_rank>=0)  MPI_Recv(fromLeft,     size_y, MPI_DOUBLE, p.left_rank,  0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        if (p.right_rank>=0) MPI_Recv(fromRight,    size_y, MPI_DOUBLE, p.right_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else{
        if (p.left_rank>=0)  MPI_Recv(fromLeft,     size_y, MPI_DOUBLE, p.left_rank,  0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (p.right_rank>=0) MPI_Recv(fromRight,    size_y, MPI_DOUBLE, p.right_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (p.left_rank>=0)  MPI_Send(&u[0][0],  1, column_type, p.left_rank,  0, MPI_COMM_WORLD);       
        if (p.right_rank>=0) MPI_Send(&u[p.xmax-p.xmin-1][0], 1, column_type, p.right_rank, 0, MPI_COMM_WORLD);   
    }

    /*-------------------------------------------------------*/
}

int ALLREDUCE(double* loc_diff, double* loc_sumdiff){

	MPI_Allreduce(loc_diff, loc_sumdiff, 1, MPI_DOUBLE, MPI_SUM,MPI_COMM_WORLD);
	return 0;

	}
int BARRIER(){
	MPI_Barrier(MPI_COMM_WORLD);
	return 0;
}
