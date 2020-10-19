#include<iostream>
#include"../test1/matrix.h"
#include<papi.h>
using namespace std;

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

    return 0;
}
