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
	int  mycount = 0, totalcount = 0, myrank, task_num, partion_size, begin,end,begin_g =
		1,end_g = 1;

	double start_time, end_time, total_time = 0, my_time = 0;

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
		end = end_g + 1;
	int length = end - begin;
	int offset[task_num],count[task_num];
	int i,k;
	MPI_Gather(&length,1,MPI_INT,count,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(count,task_num,MPI_INT,0,MPI_COMM_WORLD);
	if(myrank == 0)
	{
		for(i = 0;i < task_num;i++)
			for(offset[0] = 0,i = 1;i < task_num;offset[i] = offset[i-1] + count[i-1],i++);
	}
	MPI_Bcast(offset,task_num,MPI_INT,0,MPI_COMM_WORLD);
	bool global_prime[end_g-begin_g];
	bool local_prime[length];
	bool is_prime[end_g];
	for(int i = 3;i < end_g;i++)
	{
		if((i % 2) == 0)
			is_prime[i] = false;
		else 
			is_prime[i] = true;
		is_prime[2] = true;
	}
	for(int i = begin_g;i < end_g;i++)
		global_prime[i] = is_prime[i];
	MPI_Bcast(global_prime,end_g-begin_g,MPI_C_BOOL,0,MPI_COMM_WORLD);
	MPI_Bcast(is_prime,end_g,MPI_C_BOOL,0,MPI_COMM_WORLD);
	//printf("Process %d: length:%d offset:%d begin:%d end:%d\n",myrank,count[myrank],offset[myrank],begin,end);
	MPI_Scatterv(global_prime,count,offset,MPI_C_BOOL,local_prime,count[myrank],MPI_C_BOOL,0,MPI_COMM_WORLD);
	start_time = MPI_Wtime();
	if (myrank == 0)
	{
		int j;
		for (i = 2; i * i < end_g; i++)
		{
			if (is_prime[i])
			{
				for (j = 2 * i; j < end; j = j + i)
					local_prime[j-begin] = false;

				MPI_Bcast(&i, 1, MPI_INT, 0, MPI_COMM_WORLD);
			}
		}
		i = 0;
		printf("FIN\n");
		MPI_Bcast(&i, 1, MPI_INT, 0, MPI_COMM_WORLD);
	}

	else
	{
		int new_begin;
		while (1)
		{
			MPI_Bcast(&i, 1, MPI_INT, 0, MPI_COMM_WORLD);

			if (i == 0)
				break;

			new_begin = begin + (i - begin % i) % i;

			if (new_begin > end)
				break;

			for (k = new_begin; k < end; k += i)
				if(k != i)
					local_prime[k-begin] = false;

		}
	}
	MPI_Gatherv(local_prime,count[myrank],MPI_C_BOOL,global_prime,count,offset,MPI_C_BOOL,0,MPI_COMM_WORLD);
	end_time = MPI_Wtime();
	double max_time = 0;
	my_time = end_time - start_time;

	MPI_Reduce(&my_time, &total_time, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&my_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	FILE* fp = NULL;
	FILE* time_stats = NULL;

	fp = fopen(argv[3], "a");
	time_stats = fopen("time.dat", "a+");

	if (myrank == 0)
	{
		for(int i = 0;i < end_g - begin_g;i++)
		{
			if(global_prime[i])
			{
				totalcount++;
				fprintf(fp,"%d ",i + begin_g);
				//	printf("%d ",i+begin_g);
			}
		}
		printf("%d\n", totalcount);
		fprintf(time_stats, "%d %f %f\n", task_num, total_time, max_time);
	}

	fclose(fp);
	fclose(time_stats);
	//	free(data);
	//	free(is_prime);
	MPI_Finalize();
	exit(0);
}

void Help(char* prog_name)

{
	fprintf(stderr, "Please input the command as follow: %s <n> <m> <filename>\n", prog_name);
}
