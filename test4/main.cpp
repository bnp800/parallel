#include<iostream>
#include<fstream>
#include<mpi.h>
#include"../test1/matrix.h"

using namespace std;

int main(int argc,char* argv[])
{
    MPI_Init(&argc,&argv);
    int np,rank;
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    mat_d a,b;
    double *c;
    rff_d(argv[1],a);
    rff_d(argv[2],b);
    c = new double [a.size_y];
    int nrow = a.size_x/np;
    nrow += (a.size_x % np == 0) ? 0:1;
    int start = rank *nrow;
    int end = (rank+1) * nrow - 1;
    if(end > a.size_x-1) 
	end = a.size_x -1;

    if(end - start + 1 > 0)
	for(int i = start;i <= end;i++)
	{
	    double sum = 0;
	    for(int j = 0;j < a.size_y;j++)
		sum += a.elem[i][j] * b.elem[0][j];
	    c[i-start] = sum;
	}
    if(rank != 0)
    {
	MPI_Send(&start,1,MPI_INT,0,0,MPI_COMM_WORLD);
	MPI_Send(&end,1,MPI_INT,0,1,MPI_COMM_WORLD);
	for(int i = 0;i < end-start+1;i++)
	    MPI_Send(&c[i],1,MPI_DOUBLE,0,i+2,MPI_COMM_WORLD);
    }
    else
    {
	for(int i = 1;i < np;i++)
	{
	    MPI_Recv(&start,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	    MPI_Recv(&end,1,MPI_INT,i,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	    for(int j = start;j <= end;j++)
		MPI_Recv(&c[i],1,MPI_DOUBLE,i,j-start+2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
    }
    if(rank == 0)
    {
    for(int i = 0;i < a.size_y;i++)
	cout << c[i] << " ";
    cout << endl;
    }
    FREE(a);
    FREE(b);
    delete [] c;
    MPI_Finalize();
    return 0;
}
