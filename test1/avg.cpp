#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ifstream stats;
	stats.open("stats.dat");
	double time[60];
	int i,j;
	for(i = 0;i < 59;i++)
		stats >> time[i];
	stats.close();
	ofstream ostats;
	ostats.open("stats.dat");
	for(i = 0;i < 6;i++)
	{
		double sum = 0;
		for(j = 0;j < 9;j++)
			sum += time[i*10+j];
		ostats << i << " " << sum/10 << endl;
	}
	ostats.close();
	return 0;
}
