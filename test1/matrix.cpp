#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;

class mat_d
{
	public:
		char type;
		int size_x,size_y;
		double** elem;
};
class mat_f
{
	public:
		char type;
		int size_x,size_y;
		float** elem;
};
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
	//ifile >> in.type >> in.size_x >> in.size_y;
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
	//ifile >> in.type >> in.size_x >> in.size_y;
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
template<class T>
void mult(T& a,T& b,T& c,int mode)
{
	int i,j,k;
	switch(mode)
	{
		case 0:
			for(i = 0;i < a.size_x;i++)
				for(j = 0;j < b.size_y;j++)
				{
					double sum = 0;
					for(k = 0;k < a.size_y;k++)
						sum += a.elem[i][k]*b.elem[k][j];
					c.elem[i][j] += sum;
				}
			break;
		case 1:
			for(i = 0;i < a.size_x;i++)
				for(k = 0;k < a.size_y;k++)
				{
					double r = a.elem[i][k];
					for(j = 0;j < b.size_y;j++)
						c.elem[i][j] += r*b.elem[k][j];
				}
				break;
		case 2:
			for(k = 0;k < a.size_y;k++)
				for(i = 0;i < a.size_x;i++)
				{
					double r = a.elem[i][k];
					for(j = 0;j < b.size_y;j++)
					c.elem[i][j] += r*b.elem[k][j];
				}
				break;
		case 3:
			for(j = 0;j < b.size_y;j++)
				for(i = 0;i <a.size_x;i++)
				{
					double sum = 0;
					for(k = 0;k < a.size_y;k++)
						sum += a.elem[i][k]*b.elem[k][j];
					c.elem[i][j] += sum;
				}
				break;
		case 4:
			for(j = 0;j < b.size_y;j++)
			for(k = 0;k<a.size_y;k++)
			{
				double r = b.elem[k][j];
				for(i = 0;i < a.size_x;i++)
				c.elem[i][j] += a.elem[i][k]*r;
			}
			break;
		case 5:
			for(k = 0;k < a.size_y;k++)
				for(j = 0;j < b.size_y;j++)
				{
					double r = b.elem[k][j];
					for(i = 0;i < a.size_x;i++)
						c.elem[i][j]+=a.elem[i][k]*r;
				}
				break;
		default:
			break;
	}
}
template<class T>
void FREE(T& mat)
{
	for(int i = 0;i < mat.size_x;i++)
		delete [] mat.elem[i];
	delete [] mat.elem;
}
int main(int argc,char* argv[])
{
	try{
	char type = command_parser(argc,argv);
	int mode = 0;
	if(type == 'd')
	{
		mat_d a;
		rff_d(argv[1],a);
		for(int i = 0;i < a.size_x ;i++)
			{
			for(int j = 0;j < a.size_y;j++)
				cout <<  a.elem[i][j] << " ";
			cout << endl;
		}
		cout << endl;
		mat_d b;
		rff_d(argv[2],b);
		for(int i = 0;i < b.size_x ;i++)
			{
			for(int j = 0;j < b.size_y;j++)
				cout <<  b.elem[i][j] << " ";
			cout << endl;
		}
		cout << endl;
		mat_d c;
		c.size_x = a.size_x;
		c.size_y = b.size_y;
		c.elem = new double* [a.size_x];
		for(int i = 0;i < a.size_x;i++)
			c.elem[i] = new double [b.size_y];
			clock_t start,finish;
			ofstream out;
			out.open(argv[3],ios::binary);
			double duration;
			start = clock();
			mult(a,b,c,mode);
			finish = clock();
			duration = (double)(finish - start) /CLOCKS_PER_SEC;
			for(int i = 0;i < c.size_x ;i++)
			{
			for(int j = 0;j < c.size_y;j++)
				out.write((char*)&c.elem[i][j],sizeof(double));
			out << endl;
		}
		out.write((char*)&duration,sizeof(int));
		out.close();
			FREE(a);
			FREE(b);
			FREE(c);
	}
	if(type == 'f')
	{
		mat_f a;
		rff_f(argv[1],a);
		for(int i = 0;i < a.size_x ;i++)
			{
			for(int j = 0;j < a.size_y;j++)
				cout <<  a.elem[i][j] << " ";
			cout << endl;
		}
		cout << endl;
		mat_f b;
		rff_f(argv[2],b);
		for(int i = 0;i < b.size_x ;i++)
			{
			for(int j = 0;j < b.size_y;j++)
				cout <<  b.elem[i][j] << " ";
			cout << endl;
		}
		cout << endl;
		mat_f c;
		c.size_x = a.size_x;
		c.size_y = b.size_y;
		c.elem = new float* [a.size_x];
		for(int i = 0;i < a.size_x;i++)
			c.elem[i] = new float [b.size_y];
			clock_t start,finish;
			ofstream out;
			out.open(argv[3],ios::binary);
			double duration;
			start = clock();
			mult(a,b,c,mode);
			finish = clock();
			duration = (double)(finish - start) /CLOCKS_PER_SEC;
			for(int i = 0;i < c.size_x ;i++)
			{
			for(int j = 0;j < c.size_y;j++)
				out.write((char*)&c.elem[i][j],sizeof(float));
			out << endl;
		}
		out << endl << duration << endl;
		out.close();
			FREE(a);
			FREE(b);
			FREE(c);
	}
}
catch(const char* err)
{
	cerr << err << endl;
}
	return 0;
}
