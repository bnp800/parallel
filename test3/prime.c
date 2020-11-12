#include <stdio.h>
#define MPICH_SKIP_MPICXX
#include <mpi.h>
#include <stdlib.h>
#include <math.h>
#pragma comment(lib, "mpi.lib")
#include <stdbool.h>
#include <fcntl.h>

bool* is_prime;
int* data;

void Help(char* prog_name);
int main(int argc, char* argv[])

{
  int n, l, mycount = 0, totalcount = 0, myrank, task_num, partion_size, begin,end;

  double start_time, end_time, total_time = 0, my_time = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &task_num);

  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  if (argc != 4)
  {
    Help(argv[0]);
    exit(0);
  }

  if (myrank == 0)
  {
    l = atoi(argv[1]);
    n = atoi(argv[2]);
    is_prime = (bool*)malloc((n - l) * sizeof(bool));
    data = (int*)malloc((n - l) * sizeof(int));
  }
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&l, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (myrank != 0) 
  {
    is_prime = (bool*)malloc((n - l) * sizeof(bool));
    data = (int*)malloc((n - l) * sizeof(int));
  }

  MPI_Bcast(is_prime, n - l, MPI_C_BOOL, 0, MPI_COMM_WORLD);
  MPI_Bcast(data, n - l, MPI_INT, 0, MPI_COMM_WORLD);

  start_time = MPI_Wtime();
  partion_size = (int)ceil(n * 1.0 / task_num);
  begin = myrank * partion_size;
  end = (myrank + 1) * partion_size;

  if (begin < 2)
    begin = 2;
  if (end > n + 1)
    end = n + 1;

  int i, k;
  k = 0;

  for (i = begin; i < end; i++)
    is_prime[i] = true;
  if (myrank == 0)
  {
    int j;
    for (i = 2; i < partion_size && i * i < n; i++)
    {
      if (is_prime[i])
      {
        for (j = i * i; j < partion_size; j = j + i)
          is_prime[j] = false;

        data[k] = i;
        MPI_Bcast(data + k, 1, MPI_INT, 0, MPI_COMM_WORLD);
        k++;
      }
    }
    data[k] = 0;

    MPI_Bcast(data + k, 1, MPI_INT, 0, MPI_COMM_WORLD);
  }

  else
  {
    int new_begin;
    while (1)
    {
      MPI_Bcast(data + k, 1, MPI_INT, 0, MPI_COMM_WORLD);

      if (data[k] == 0)
        break;

      new_begin = begin + (data[k] - begin % data[k]) % data[k];

      if (new_begin > end)
        break;

      for (i = new_begin; i < end; i += data[k])
        is_prime[i] = false;

      k++;
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

  if (begin < l)
    begin = l;
  for (i = begin; i < end; i++)
    if (is_prime[i])
    {
      fprintf(fp, "%d ", i);
      mycount++;
    }

  MPI_Reduce(&mycount, &totalcount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (myrank == 0)
  {
    printf("Total found %d prime numbers\n", totalcount);
    fprintf(time_stats, "%d %f %f\n", task_num, total_time, max_time);
  }

  fclose(fp);
  fclose(time_stats);
  free(data);
  free(is_prime);
  MPI_Finalize();

  if (myrank != 0)
    exit(0);
  else
    return 0;
}

void Help(char* prog_name)

{
  fprintf(stderr, "Please input the command as follow: %s <n> <m> <filename>\n", prog_name);
}
