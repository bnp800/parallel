#include <stdio.h>
#define MPICH_SKIP_MPICXX
#include <mpi.h>
#include <stdlib.h>
#include <math.h>
#pragma comment(lib, "mpi.lib")
#include <stdbool.h>
#include <fcntl.h>



void Help(char* prog_name);
int main(int argc, char* argv[])

{
	int  mycount = 0, totalcount = 0, myrank, task_num, partion_size, begin,end,begin_g = 1,end_g = 1;
	double start_time, end_time, total_time = 0, my_time = 0;
//	bool* global_prime;
	bool* local_prime;
	bool* is_prime;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &task_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	if (argc != 4)
	{
		Help(argv[0]);
		exit(0);
	}


	begin_g = atoi(argv[1]);
	end_g = atoi(argv[2]);

	partion_size = (int)floor((end_g-begin_g) * 1.0 / task_num);
	begin = (myrank) * partion_size + begin_g;
	end = (myrank + 1) * partion_size + begin_g;
	if(myrank == task_num - 1)
		end = end_g;
	int length = end - begin;
	int i,k,root = floor(sqrt(end_g));

//	global_prime = (bool*)malloc((end_g-begin_g) * sizeof(bool));
	local_prime = (bool*)malloc(length * sizeof(bool));
	is_prime = (bool*)malloc(root * sizeof(bool));
//	MPI_Bcast(global_prime,end_g-begin_g,MPI_C_BOOL,0,MPI_COMM_WORLD);
	MPI_Bcast(is_prime,root,MPI_C_BOOL,0,MPI_COMM_WORLD);
	for(i = 2;i < root;i++)
	{
		if((i % 2) == 0)
			is_prime[i] = false;
		else 
			is_prime[i] = true;
	}
	is_prime[2] = true;
	for(i = 0;i < length;i++)
		local_prime[i]=true;
	start_time = MPI_Wtime();
	if (myrank == 0)
	{
		int j;
		for (i = 2; i  < root; i++)
		{
			if (is_prime[i])
			{
				for (j = begin + (i - begin % i) % i; j < end; j = j + i)
					if(j != i)
						local_prime[j-begin] = false;
				for(j = i+i;j < root;j += i)
					is_prime[j] = false;
			}
		}
		MPI_Bcast(is_prime, root, MPI_C_BOOL, 0, MPI_COMM_WORLD);
	}

	else
	{
		MPI_Bcast(is_prime, root, MPI_C_BOOL, 0, MPI_COMM_WORLD);
		for(int l = 2;l < root;l++)
		{
			if(is_prime[l])
			{
				for (k = begin + (l - begin % l) % l; k < end; k+=l)
					if(k != l)
						local_prime[k-begin] = false;
			}

		}
	}
	end_time = MPI_Wtime();
	double max_time = 0;
	my_time = end_time - start_time;

	MPI_Reduce(&my_time, &total_time, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&my_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	FILE* fp = NULL;
	FILE* time_stats = NULL;


	fp = fopen(argv[3], "a");
	time_stats = fopen("time.dat", "a+");
	for(i = begin;i < end;i++)
	{
		if(local_prime[i - begin])
		{
			mycount++;
			fprintf(fp,"%d ",i);
		}
	}
	MPI_Reduce(&mycount,&totalcount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (myrank == 0)
	{
		printf("%d\n", totalcount);
		fprintf(time_stats, "%d %f %f\n", task_num, total_time, max_time);
	}
	fclose(fp);
	fclose(time_stats);

	free(is_prime);
//	free(global_prime);
	free(local_prime);
	MPI_Finalize();
	exit(0);
}

void Help(char* prog_name)

{
	fprintf(stderr, "Please input the command as follow: %s <n> <m> <filename>\n", prog_name);
}
