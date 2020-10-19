#include<iostream>
#include"../test1/matrix.h"
#include<papi.h>
#include<cstdlib>
#include<unistd.h>
#include<cmath>
#include<fstream>
using namespace std;

#define N 1024
void blockMult(mat_f &a,mat_f &b1,mat_f &c,int b,int mode)
{
    int i,j,k;
    switch(mode)
    {
	case 0:
	    for(i = 0;i < a.size_x;i+=b)
		for(j = 0;j < a.size_y;j+=b)
		    for(k = 0;k < a.size_x;k+=b)
			for(int i1 = i;i1 < i+b;i1++)
			    for(int j1 = j;j1 < j+b;j1++)
				for(int k1 = k;k1 < k+b;k1++)
				    c.elem[i1][j1] += a.elem[i1][k1]*b1.elem[k1][j1];
	    break;
	case 1:
	    for(i = 0;i < a.size_x;i+=b)
		for(j = 0;j < a.size_y;j+=b)
		    for(k = 0;k < a.size_x;k+=b)
			for(int i1 = i;i1 < i+b;i1++)
			    for(int k1 = k;k1 < k+b;k1++)
				for(int j1 = j;j1 < j+b;j1++)
				    c.elem[i1][j1] += a.elem[i1][k1]*b1.elem[k1][j1];
	    break;
	default:
	    break;
    }

}
int powf2(double b)
{
    int n = 2;
    if(n <= b)
	n *= 2;
    return n;
}
void output(mat_f& c,char* name)
{
    ofstream out;
    out.open(name,ios::binary);
    out.write((char*)&c.size_x,sizeof(int));
    out.write((char*)&c.size_y,sizeof(int));
    for(int i = 0;i < N;i++)
	for(int j = 0;j < N;j++)
    out.write((char*)&c.elem[i][j],sizeof(float));
    out.close();
}
int main(int argc,char* argv[])
{
    int retval,EventSet = PAPI_NULL;
    PAPI_event_info_t info;
    retval = PAPI_library_init(PAPI_VER_CURRENT);

    if(retval != PAPI_VER_CURRENT)
    {
	cerr << "PAPI library ini error" << endl;
	exit(1);
    }
    mat_f a,b,c;
    int mode = atoi(argv[4]);
    int bb = 32;
    //double bb = sqrt(sysconf(_SC_LEVEL1_DCACHE_SIZE) / sysconf(_SC_LEVEL1_DCACHE_ASSOC)/3);
    //(int)bb = powf2(bb);
    rff_f(argv[1],a);
    rff_f(argv[2],b);
    c.size_x = c.size_y = N;
    c.elem = new float* [N];
    for(int i = 0;i < N;i++)
	c.elem[i] = new float [N];
	for(int i = 0;i < N;i++)
	    for(int j = 0;j < N;j++)
		c.elem[i][j] = 0;
    blockMult(a,b,c,bb,mode);
    output(c,argv[3]);
    FREE(a);
    FREE(b);
    FREE(c);
    return 0;
}
