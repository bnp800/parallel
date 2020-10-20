#include<iostream>
#include"../test1/matrix.h"
#include<papi.h>
#include<cstdlib>
#include<unistd.h>
#include<cmath>
#include<fstream>
#include"blockmult.h"
#include<cstring>
using namespace std;

#define N 2048
int min2(double b)
{
    int n = 2;
    if(n <= b)
	n *= 2;
    return n;
}
void stats(int mode,long long* counters,long long begin_time,long long end_time)
{
    ofstream out,out1,out2,out3,out4,out5;
    out.open("stats_time.dat" , ios::app);
    out1.open("stats_L1_miss_rate.dat" , ios::app);
    out2.open("stats_L2_miss_rate.dat" , ios::app);
    out3.open("stats_cycles.dat" , ios::app);
    out4.open("stats_FLOP.dat" , ios::app);
    out5.open("stats_TLB.dat" , ios:: app);

    out << mode << " " << (double)(end_time - begin_time) / 1000 << endl;
    out1 << mode << " " << (double)counters[1] / (double)counters[2] << endl;
    out2 << mode << " " << (double)counters[3] / (double)counters[4] << endl;
    out3 << mode << " " << counters[0] << endl;
    out4 << mode << " " << counters[5] << endl;
    out5 << mode << " " << counters[6]<< endl;
	out.close();
	out1.close();
	out2.close();
	out3.close();
	out4.close();
	out5.close();

}
void output(mat_f& c,char* name)
{
    char type = 'f';
    ofstream out;
    out.open(name,ios::binary);
    out.write((char*)&type,sizeof(char));
    out.write((char*)&c.size_x,sizeof(int));
    out.write((char*)&c.size_y,sizeof(int));
    for(int i = 0;i < N;i++)
	for(int j = 0;j < N;j++)
    out.write((char*)&c.elem[i][j],sizeof(float));
    out.close();
}
int main(int argc,char* argv[])
{
    int retval;
    int PAPI_EVENTS[] = {PAPI_TOT_CYC,PAPI_L1_DCM,PAPI_L1_DCA,PAPI_L2_DCM,PAPI_L2_DCA,PAPI_FP_OPS,PAPI_TLB_DM};
    long long counters[7];
    long long begin_time,end_time;
    PAPI_event_info_t info;
    retval = PAPI_library_init(PAPI_VER_CURRENT);

    if(retval != PAPI_VER_CURRENT)
    {
	cerr << "PAPI library ini error" << endl;
	exit(1);
    }

    mat_f a,b,c;
    int mode  = atoi(argv[4]);
    int bb = 32;
  //  int bb = sqrt(sysconf(_SC_LEVEL1_DCACHE_SIZE) / sysconf(_SC_LEVEL1_DCACHE_ASSOC)/3);
   // bb = min2(bb);
    rff_f(argv[1],a);
    rff_f(argv[2],b);
    c.size_x = c.size_y = N;
    c.elem = new float* [N];
    for(int i = 0;i < N;i++)
	c.elem[i] = new float [N];
	for(int i = 0;i < N;i++)
	    for(int j = 0;j < N;j++)
		c.elem[i][j] = 0;

	int init = PAPI_start_counters(PAPI_EVENTS,7);
	begin_time = PAPI_get_real_usec();
    blockMult(a,b,c,bb,mode);
	end_time = PAPI_get_real_usec();
    PAPI_read_counters(counters,7);
	stats(mode,counters,begin_time,end_time);
    output(c,argv[3]);
    FREE(a);
    FREE(b);
    FREE(c);
    return 0;
}
