#include<iostream>
#include<pthread.h>
#include<cstdlib>
#include<fstream>
#include<math.h>
#include<time.h>
using namespace std;

bool *is_prime;
int* data;
double totaltime = 0,maxtime = 0;
struct thread_data
{
    int start;
    int end;
    int num;
};
void* primes(void *ptr)
{
    double begintime,endtime;
    struct thread_data *my_data;
    my_data = (struct thread_data*)ptr;
    int newbegin = my_data->start + (my_data->num - my_data->start % my_data->num) % my_data->num;
    if(newbegin > my_data->end)
	pthread_exit(NULL);
    for(int i = newbegin;i < my_data->end;i += my_data->num)
	is_prime[i] = false;
    pthread_exit(NULL);
}
int main(int argc,char* argv[])
{
    int num = atoi(argv[1]),begin = atoi(argv[2]),end = atoi(argv[3]);
    clock_t begintime,endtime;
    struct thread_data td[num];
    is_prime = new bool [end-begin];
    data = new int [end-begin];
    int partion_size = (int)ceil((end - begin) * 1. / num);
    pthread_t tids[num];
    clock_t total_begin = clock();

    for(int i = 0;i < end;i++)
	is_prime[i] = true;

    for(int j = 2;j < partion_size && j * j < end;j++)
    {
	if(is_prime[j])
	{
	    for(int k = j + j;k <= partion_size;k+=j)
		is_prime[k] = false;
	    for(int i = 1;i < num;i++)
	    {
		td[i].num = j;
		td[i].start = i * partion_size;
		td[i].end = (i+1) * partion_size;
		if(td[i].start < 2)
		    td[i].start = 2;
		if(td[i].end > end + 1)
		    td[i].end = end + 1;

    begintime = clock();
		int ret = pthread_create(&tids[i],NULL,primes,(void*) &td[i]);
    endtime = clock();

    double mytime = (double)(endtime - begintime) / CLOCKS_PER_SEC;
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
	}
    }

    clock_t total_end = clock();
    totaltime = (double)(total_end - total_begin) / CLOCKS_PER_SEC;

    if(num == 1)
	maxtime = totaltime;

    int count = 0;
    ofstream out,time;
    out.open("primes.txt",ios::out);
    time.open("pthread_time.dat",ios::out | ios::app);
    if(begin < 2)
	begin = 2;
    for(int i = begin;i < end;i++)
    {
	if(is_prime[i])
	{
	    count++;
	    out << i << " ";
	}
    }
    time << num << " " << totaltime << " " << maxtime << endl;

    cout << count << endl;

    out.close();
    time.close();
    delete [] is_prime;
    delete [] data;
    pthread_exit(NULL);
}
