#include<iostream>
#include<fstream>

using namespace std;

void minmax(double* time)
{
    double min,max;
    int min_num,max_num;
    
	    for(int i = 0;i < 5;i++)
	    {
		min = max = time[i*10];
		for(int j = 0;j < 9;j++)
		{
			if(time[i*10+j] > max)
			{
			    max = time[i*10+j];
				max_num = i*10+j;
			}
			 if(time[i*10+j] < min)
			 {
			     min = time[i*10+j];
			     min_num = i*10+j;
			 }
		}
		time[max_num] = 0;
		time[min_num] = 0;
	}
}
int main(int argc,char* argv[])
{
	ifstream stats;
	stats.open(argv[1]);
	double time[60];
	int i,j;
	for(i = 0;i < 59;i++)
		stats >> time[i];
	stats.close();
	ofstream ostats;
	ostats.open(argv[1]);
	minmax(time);
	for(i = 0;i < 5;i++)
	{
		double sum = 0;
		for(j = 0;j < 9;j++)
			sum += time[i*10+j];
		ostats << i << " " << sum/8<< endl;
	}
	ostats.close();
	return 0;
}
