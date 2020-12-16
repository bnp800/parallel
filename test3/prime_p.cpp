#include<iostream>
#include<pthread.h>
#include<cstdlib>
#include<fstream>
#include<math.h>
#include<time.h>
using namespace std;

bool *is_prime;
double totaltime = 0,maxtime = 0;
struct thread_data
{
	int start;
	int end;
	int num;
	int offset;
};
void* primes(void *ptr)
{
	struct thread_data *my_data;
	my_data = (struct thread_data*)ptr;
	int newbegin = my_data->start + (my_data->num - my_data->start % my_data->num) % my_data->num;
	if(newbegin > my_data->end)
		pthread_exit(NULL);
	for(int i = newbegin;i < my_data->end;i += my_data->num)
		if(i != my_data->num)
			is_prime[i] = false;
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
	is_prime = new bool [end+1];
	int partion_size = (int)ceil((end-begin+1) * 1. / num);
	pthread_t tids[num];

	for(int i = 3;i <= end;i++)
	{
		if(i % 2 != 0)
			is_prime[i] = true;
		if(i % 2 == 0)
			is_prime[i] = false;
	}
	is_prime[2] = true;
	clock_gettime(CLOCK_MONOTONIC,&total_begin);
	for(int j = 3; j*j < end;j++)
	{
		if(is_prime[j])
		{
			for(int k = j+j;k*k < end;k+=j)
				is_prime[k] = false;
			for(int i = 0;i < num;i++)
			{
				td[i].num = j;
				td[i].start = i * partion_size + begin;
				td[i].end = (i+1) * partion_size + begin;
				if(td[i].end > end + 1)
					td[i].end = end + 1;

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

			for(int l = 1;l < num;l++){
				int rc = pthread_join(tids[l],NULL);
				if(rc)
				{
					cerr << "can't join thread:" << rc << endl;
					exit(-2);
				}
			}
			// }
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
	for(int i = begin;i <= end;i++)
{
	if(is_prime[i])
	{
		count++;
		out << i<< " ";
	}
}
//    cout << num << " " << totaltime << " " << maxtime << endl;

cout <<endl<< count << endl;

out.close();
time.close();
pthread_exit(NULL);
}
