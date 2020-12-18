#include<iostream>
#include<pthread.h>
#include<cstdlib>
#include<fstream>
#include<math.h>
#include<time.h>
using namespace std;

bool *is_prime;
bool *global_prime;
double totaltime = 0,maxtime = 0;
struct thread_data
{
	int start;
	int end;
	int root;
	int offset;
};
void* primes(void *ptr)
{
	struct thread_data *my_data;
	my_data = (struct thread_data*)ptr;
	int j;
	for(j = 2;j < my_data->root;j++)
	{
		if(is_prime[j])
		{
			int newbegin = my_data->start + (j - my_data->start % j) % j;
			if(newbegin == j)
				newbegin = j+j;
			for(int i = newbegin;i < my_data->end;i += j)
				{
					global_prime[i-my_data->offset] = false;
				}

		}
	}
			pthread_exit(NULL);
}
bool is_primef(int num)
{
	for(int i = 3;i * i < num;i+=2)
		if(num % i == 0)
			return false;
	return true;
}
int main(int argc,char* argv[])
{
	int num = atoi(argv[1]),begin = atoi(argv[2]),end = atoi(argv[3]);
	struct timespec begintime,endtime,total_begin,total_end;
	struct thread_data td[num];
	int root = floor(sqrt(end)),length = end-begin;
	is_prime = new bool [root];
	global_prime = new bool [length];
	int partion_size = (int)floor((end-begin) * 1. / num);
	pthread_t tids[num];

	for(int i = 2;i < root;i++)
	{
		if((i % 2) != 0)
			is_prime[i] = true;
		if((i % 2) == 0)
			is_prime[i] = false;
	}
	is_prime[2] = true;
	for(int i = 0;i < length;i++)
		global_prime[i] = true;
	clock_gettime(CLOCK_MONOTONIC,&total_begin);
	for(int j = 2; j < root;j++)
	{
		if(is_prime[j])
		{
			for(int k = j+j;k < root;k+=j)
			{
				is_prime[k] = false;
			}
		}
	}
	for(int i = 0;i < num;i++)
	{
		td[i].root = root;
		td[i].start = i * partion_size + begin;
		td[i].end = (i+1) * partion_size + begin;
		td[i].offset = begin;
		if(i == num - 1)
			td[i].end = end;
	//	cout << "process: " << i << " start: " << td[i].start << " end: " << td[i].end << " root: " << root << endl;
		clock_gettime(CLOCK_MONOTONIC,&begintime);
		int ret = pthread_create(&tids[i],NULL,primes,(void*) &td[i]);
		clock_gettime(CLOCK_MONOTONIC,&endtime);

		double mytime = endtime.tv_sec - begintime.tv_sec +
			(endtime.tv_nsec - begintime.tv_nsec)/1000000000.0;
		if(mytime > maxtime)
			maxtime = mytime;

		if(ret)
		{
			cerr << "Error create thread:" << ret << endl;
			exit(-1);
		}
	}

	for(int l = 0;l < num;l++){
		int rc = pthread_join(tids[l],NULL);
		if(rc)
		{
			cerr << "can't join thread:" << rc << endl;
			exit(-2);
		}
	}


clock_gettime(CLOCK_MONOTONIC,&total_end);
totaltime = total_end.tv_sec - total_begin.tv_sec + (total_end.tv_nsec - total_begin.tv_nsec)/1000000000.0;

if(num == 1)
	maxtime = totaltime;

	int count = 0;
	ofstream out,time;
	out.open("primes_p.txt",ios::out);
	time.open("pthread_time.dat",ios::out | ios::app);
	for(int i = 0;i < end-begin;i++)
{
	if(global_prime[i])
	{
		count++;
		out << i + begin<< " ";
	}
}
    time << num << " " << totaltime << " " << maxtime << endl;

cout << count << endl;

out.close();
time.close();
pthread_exit(NULL);
}
