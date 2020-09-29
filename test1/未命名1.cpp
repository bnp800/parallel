#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main()
{
	ofstream outfile("b.txt",ios::binary | ios::out);
	unsigned seed;
	seed = time(0);
	srand(seed);
	int size_x,size_y;
	cin >> size_x >> size_y;
	char c;
	cin >> c;
	outfile.write((char*)&c,sizeof(char));
	outfile.write((char*)&size_x,sizeof(int));
	outfile.write((char*)&size_y,sizeof(int));
	if(c == 'd')
	{
		double num;
	for(int i = 0;i < size_x*size_y;i++)
	{
		num = rand();
		outfile.write((char*)&num,sizeof(double));
	}
	return 0;
	}
	if(c == 'f')
	{
		float num;
		for(int i = 0;i < size_x*size_y;i++)
		{
			num = rand();
			outfile.write((char*)&num,sizeof(float));
			}	
	}
	
	outfile.close();
	return 0;
}
