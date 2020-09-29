#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main(int argc,char* argv[])
{
	ofstream outfile(argv[1],ios::binary | ios::out);
	ofstream outfile1(argv[2],ios::binary | ios::out);
	unsigned seed;
	seed = time(0);
	srand(seed);
	int size_x = 50;
	int size_y = 50;
	char c = argv[3][1];
	outfile.write((char*)&c,sizeof(char));
	outfile.write((char*)&size_x,sizeof(int));
	outfile.write((char*)&size_y,sizeof(int));
	outfile1.write((char*)&c,sizeof(char));
	outfile1.write((char*)&size_x,sizeof(int));
	outfile1.write((char*)&size_y,sizeof(int));
	if(c == 'd')
	{
		double num;
		for(int i = 0;i < size_x*size_y;i++)
		{
			num = rand();
			outfile.write((char*)&num,sizeof(double));
			num = rand();
			outfile1.write((char*)&num,sizeof(double));
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
			num = rand();
			outfile.write((char*)&num,sizeof(float));
		}	
	}

	outfile.close();
	outfile1.close();
	return 0;
}
