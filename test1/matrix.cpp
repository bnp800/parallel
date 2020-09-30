#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include"matrix.h"
using namespace std;

char command_parser(int num,char** command)
{
	if(num != 5)
		throw "invalid arg num";
	int mode = atoi(command[4]);
	if((mode < 0) || (mode > 5))
		throw "invalid index mode";
	ifstream in;
	in.open(command[1],ios::binary | ios::in);
	char type;
	in.read((char*)&type,sizeof(char));
	in.close();
	return type;
}
void rff_d(char* name,mat_d& in)
{
	ifstream ifile;
	ifile.open(name,ios::binary);
	ifile.read((char*)&in.type,sizeof(char));
	ifile.read((char*)&in.size_x,sizeof(int));
	ifile.read((char*)&in.size_y,sizeof(int));
	in.elem = new double* [in.size_x];
		for(int i = 0;i < in.size_x;i++)
			in.elem[i] = new double [in.size_y];
	for(int i = 0;i < in.size_x ;i++)
		for(int j = 0;j < in.size_y;j++)
			ifile.read((char*)&in.elem[i][j],sizeof(double));
	ifile.close();
}
void rff_f(char* name,mat_f& in)
{
	ifstream ifile;
	ifile.open(name,ios::binary);
	ifile.read((char*)&in.type,sizeof(char));
	ifile.read((char*)&in.size_x,sizeof(in.size_x));
	ifile.read((char*)&in.size_y,sizeof(in.size_y));
	in.elem = new float* [in.size_x];
		for(int i = 0;i < in.size_x;i++)
			in.elem[i] = new float [in.size_y];
	for(int i = 0;i < in.size_x ;i++)
		for(int j = 0;j < in.size_y;j++)
			ifile.read((char*)&in.elem[i][j],sizeof(float));
	ifile.close();
}
