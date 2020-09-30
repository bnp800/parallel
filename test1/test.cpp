#include<iostream>
#include<fstream>
#include"matrix.h"

using namespace std;

int main(int argc,char** argv)
{
	ifstream in1(argv[1],ios::binary | ios::in);
	char type;
	in1.read((char*)&type,sizeof(char));
	in1.close();
	bool flag = 1;
	if(type == 'd')
	{
		mat_d a,b,c,d;
		int i,j;
		rff_d(argv[1],a);
		rff_d(argv[2],b);
		rff_d(argv[3],d);
                 c.size_x = d.size_x;
                 c.size_y = d.size_y; 
                 c.elem = new double* [c.size_x];
                 for(int i = 0;i < c.size_x;i++)
                         c.elem[i] = new double [c.size_y];
		mult(a,b,c,0);
		for(i = 0;i < c.size_x;i++)
			for(j = 0;j < c.size_y;j++)
				if(c.elem[i][j] != d.elem[i][j])
				{
					flag = 0;
					break;
				}
		FREE(a);
		FREE(b);
		FREE(c);
		FREE(d);
	}
	if(type == 'f')
	{
		mat_f a,b,c,d;
		int i,j;
		rff_f(argv[1],a);
		rff_f(argv[2],b);
		rff_f(argv[3],d);
                 c.size_x = d.size_x;
                 c.size_y = d.size_y;
                 c.elem = new float* [c.size_x];
                 for(int i = 0;i < c.size_x;i++)
                         c.elem[i] = new float [c.size_y];
		mult(a,b,c,0);
		for(i = 0;i < c.size_x;i++)
			for(j = 0;j < c.size_y;j++)
				if(c.elem[i][j] != d.elem[i][j])
				{
					flag = 0;
					break;
				}
		FREE(a);
		FREE(b);
		FREE(c);
		FREE(d);
	}
		if(flag)
			cout << "correct" << endl;
		else
			cout << "error" << endl;
	return 0;
}
