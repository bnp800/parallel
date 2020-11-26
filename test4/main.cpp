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
    double *c,*d;
    rff_d(argv[1],a);
    rff_d(argv[2],b);
    c = new double [a.size_y];
    d = new double [a.size_y];
    int nrow = a.size_x/np;
    int ncol = a.size_y/np;
    nrow += (a.size_x % np == 0) ? 0:1;
    ncol += (a.size_y % np == 0) ? 0:1;
    int startrow = rank *nrow;
    int endrow = (rank+1) * nrow - 1;
    int startcol = rank * ncol;
    int endcol = (rank+1) * ncol - 1;
    if(endrow > a.size_x-1) 
	endrow = a.size_x -1;
    if(endcol > a.size_y -1)
	endcol = a.size_x -1;
    for(int i = 0;i < a.size_y;i++)
	d[i] = 0;

//    cout << "Begin" << endl;
    if(endrow - startrow + 1 > 0)
	for(int i = startrow;i <= endrow;i++)
	{
	    double sum = 0;
	    for(int j = 0;j < a.size_y;j++)
		sum += a.elem[i][j] * b.elem[0][j];
	    c[i-startrow] = sum;
	}
  //  cout << "Row" << endl;
    if(endcol - startcol + 1 > 0)
    	for(int j = startcol;j <= endcol;j++)
	{
	    for(int i = 0;i < a.size_x;i++)
		d[i-startcol] += a.elem[i][j] * b.elem[0][j];
	   // d[j-startcol] = sum;
	}
    if(rank != 0)
    {
	MPI_Send(&startrow,1,MPI_INT,0,0,MPI_COMM_WORLD);
	MPI_Send(&endrow,1,MPI_INT,0,1,MPI_COMM_WORLD);
	for(int i = 0;i < endrow-startrow+1;i++)
	    MPI_Send(&c[i],1,MPI_DOUBLE,0,i+2,MPI_COMM_WORLD);
	MPI_Send(&startcol,1,MPI_INT,0,0,MPI_COMM_WORLD);
	MPI_Send(&endcol,1,MPI_INT,0,1,MPI_COMM_WORLD);
	for(int i = 0;i < endcol-startcol+1;i++)
	    MPI_Send(&d[i],1,MPI_DOUBLE,0,i+2,MPI_COMM_WORLD);
    }
    else
    {
	for(int i = 1;i < np;i++)
	{
	    MPI_Recv(&startrow,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	    MPI_Recv(&endrow,1,MPI_INT,i,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	    for(int j = startrow;j <= endrow;j++)
		MPI_Recv(&c[i],1,MPI_DOUBLE,i,j-startrow+2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
	for(int i = 1;i < np;i++)
	{
	    MPI_Recv(&startcol,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	    MPI_Recv(&endcol,1,MPI_INT,i,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	    for(int j = startcol;j <= endcol;j++)
		MPI_Recv(&d[i],1,MPI_DOUBLE,i,j-startcol+2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
    }
    if(rank == 0)
    {
	ofstream out(argv[3],ios::out | ios::binary);
	cout << endl;
    for(int i = 0;i < a.size_y;i++)
	cout << c[i] << " ";
    cout << endl;
    cout << "_______" << endl;
    cout << endl;
    for(int i = 0;i < a.size_y;i++)
	cout << d[i] << " ";
    cout << endl;
    for(int i = 0;i < a.size_y;i++)
	out.write((char*)&c[i],sizeof(double));
    out.close();
    }
    FREE(a);
    FREE(b);
    delete [] c;
    delete [] d;
    MPI_Finalize();
    return 0;
}
