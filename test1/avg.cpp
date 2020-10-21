#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

int main(int argc,char* argv[])
{
	ifstream stats;
	stats.open(argv[1]);
	int i,j,num = atoi(argv[2]);
	double time[6*num];
	for(i = 0;i < num*6;i++)
		stats >> time[i];
	stats.close();
	ofstream ostats;
	ostats.open(argv[1]);
	for(i = 0;i < 6;i++)
	{
		double sum = 0;
		for(j = 0;j < num;j++)
			sum += time[i*num+j];
		ostats << i << " " << sum/num<< endl;
	}
	ostats.close();
	return 0;
}
