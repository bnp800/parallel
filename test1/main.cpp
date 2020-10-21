#include<iostream>
#include<fstream>
#include<ctime>
#include"matrix.h"
#include<cstdlib>
using namespace std;

int main(int argc,char* argv[])
 {
         try{
         char type = command_parser(argc,argv);
         int mode = atoi(argv[4]);
         if(type == 'd')
         {
                 mat_d a;
                 rff_d(argv[1],a);
                 mat_d b;
                 rff_d(argv[2],b);
                 mat_d c; 
                 c.size_x = a.size_x;
                 c.size_y = b.size_y; 
                 c.elem = new double* [a.size_x];
                 for(int i = 0;i < c.size_x;i++)
                         c.elem[i] = new double [b.size_y];
		 for(int i = 0;i < c.size_x;i++)
			 for(int j = 0;j < c.size_y;j++)
				 c.elem[i][j] = 0;
                         clock_t start,finish;
                         ofstream out;
                         out.open(argv[3],ios::binary);
                         double duration;
                         start = clock();
                         mult(a,b,c,mode);
                         finish = clock();
                         duration = (double)(finish - start) /CLOCKS_PER_SEC;
			 out.write((char*)&type,sizeof(char));
			 out.write((char*)&c.size_x,sizeof(int));
			 out.write((char*)&c.size_y,sizeof(int));
                         for(int i = 0;i < c.size_x ;i++)
                 	        for(int j = 0;j < c.size_y;j++)
                        	         out.write((char*)&c.elem[i][j],sizeof(double));
                 out.close();
		 ofstream stats("stats.dat",ios::app);
		 stats << duration << endl;
		 stats.close();
                         FREE(a);
                         FREE(b);
                         FREE(c);
         }
         if(type == 'f')
         {
                 mat_f a;
                 rff_f(argv[1],a);
                 mat_f b;
                 rff_f(argv[2],b);
                 mat_f c;
                 c.size_x = a.size_x;
                 c.size_y = b.size_y;
                 c.elem = new float* [a.size_x];
                 for(int i = 0;i < a.size_x;i++)
                         c.elem[i] = new float [b.size_y];
		 for(int i = 0;i < c.size_x;i++)
			 for(int j = 0;j < c.size_y;j++)
				 c.elem[i][j] = 0;
                         clock_t start,finish;
                         ofstream out;
                         out.open(argv[3],ios::binary);
                         double duration;
                         start = clock();
                         mult(a,b,c,mode);
                         finish = clock();
                         duration = (double)(finish - start) /CLOCKS_PER_SEC;
			 out.write((char*)&type,sizeof(char));
			 out.write((char*)&c.size_x,sizeof(int));
			 out.write((char*)&c.size_y,sizeof(int));
                         for(int i = 0;i < c.size_x ;i++)
                         {
                         for(int j = 0;j < c.size_y;j++)
                                 out.write((char*)&c.elem[i][j],sizeof(float));
                 }
                 out.close();
		 ofstream stats("stats.dat",ios::app);
		 stats <<  duration << endl;
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

