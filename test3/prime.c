#include <stdio.h>
#define MPICH_SKIP_MPICXX
#include <mpi.h>
#include <stdlib.h>
#include <math.h>
#pragma comment(lib,"mpi.lib")
#include<stdbool.h>

bool is_prime[512100];
int data[1500]; //起步素数

void Help(char* prog_name); //usage of the program

/*  ------------------------------------------------------------------- 
 *  主程序 
 *  ------------------------------------------------------------------- */ 
int main(int argc, char* argv[])

{

    int n,          //问题规模
        mycount,    //单个进程中素数个数
        allcount,   //总的素数个数
        myrank,     //子任务标识
        task_num,   //子任务个数
        partion_size,       //子问题规模
        begin,      //数据区间左端点
        end;        //数据区间右端点

    double  start_time,     //开始时间
            end_time,       //结束时间
            total_time,     //总时间（取所有进程时间中的最大值）
            my_time;        //单个进程的时间

    mycount = 0;

    allcount = 0;

    MPI_Init(&argc,&argv);  //MPI程序初始化

    MPI_Comm_size(MPI_COMM_WORLD,&task_num);    //取子任务个数

    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);      //取子任务标识

    if (argc != 2)      //参数个数为2：文件名以及问题规模n

    {

        Help(argv[0]);

        exit(0);

    }

    if (myrank == 0)

    {

        n=atoi(argv[1]);

    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);   //主程序将获取的参数n广播

    start_time= MPI_Wtime();    //开始时间

    partion_size = (int)ceil(n*1.0/task_num);   //每个进程划分得到的数据规模

    //左闭右开
    begin = myrank * partion_size;

    end = (myrank+1) * partion_size;

    //保证第一组数据从2开始
    if (begin < 2)

        begin = 2;

    //保证最后一组数据不越界
    if (end > n+1)

        end = n+1;

    int i, k;

    k = 0;

    for (i = begin; i < end; i++)

        is_prime[i] = true;

    if (myrank == 0)    //主程序

    {
        int j;

        fprintf (stdout, "\n正在使用%d个子任务，在查找%d之内的素数.\n",task_num,n);

        for (i = 2; i < partion_size && i*i < n; i++)

        {

            if(is_prime[i])

            {

                for (j = i*i; j < partion_size; j = j+i)

                    is_prime[j] = false;

                data[k] = i;

                //每找到一个素数就广播
                //注意，广播的第3个参数指定了广播发送方，第4个参数指定了群组，群组中其他进程为接收方。
                MPI_Bcast(data+k, 1, MPI_INT, 0, MPI_COMM_WORLD);

                k++;

            }

        }

        data[k] = 0;

        //广播0表示结束
        MPI_Bcast(data+k, 1, MPI_INT, 0, MPI_COMM_WORLD);

    }

    else    //从程序

    {

        int new_begin;

        while (1)

        {

            //接收来自主程序的广播
            MPI_Bcast(data+k, 1, MPI_INT, 0, MPI_COMM_WORLD);

            //接收到0表示结束
            if (data[k] == 0)   break;  

            //本区间中第一个能被data[k]整除的数
            new_begin = begin+(data[k]-begin%data[k])%data[k];

            if (new_begin>end)  break;

            //筛掉data[k]的倍数
            for (i = new_begin; i < end; i += data[k])

                    is_prime[i] = false;

            k++;

        }

    }

    fprintf (stdout, "\nI'm process %d,the primes I found are:\n",myrank);

    for (i = begin; i < end; i++)

        if(is_prime[i])

        {
            mycount++;

            fprintf(stdout, "%d ", i);

        }

    fprintf(stdout, "\n");

    //素数个数归约
    MPI_Reduce(&mycount,&allcount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD); 

    end_time = MPI_Wtime();

    my_time = end_time - start_time;

    //printf("\nI'm process %d,my running time is %f seconds\n",myrank,my_time);

    //执行时间归约
    MPI_Reduce(&my_time,&total_time,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD); 

    if(myrank==0)

    {

        printf("\nTotal count of prime number:%d\n",allcount);              

        printf("Elapsed time = %f seconds\n",total_time);

        fflush(stdout);

    }

    MPI_Finalize();

    return 0;

}

void Help(char* prog_name) 

{

    fprintf(stderr, "Please input the command as follow: %s <n> \n", prog_name);

    fprintf(stderr, " (n: number of elements)\n");

}
