#include<iostream>

using namespace std;


void blockMult(mat_f &a,mat_f &b1,mat_f &c,int b,int mode)
{
    int i,j,k;
    switch(mode)
    {
	case 0:
	    for(i = 0;i < a.size_x;i+=b)
		for(j = 0;j < a.size_y;j+=b)
		    for(k = 0;k < a.size_x;k+=b)
			for(int i1 = i;i1 < i+b;i1++)
			    for(int j1 = j;j1 < j+b;j1++)
				for(int k1 = k;k1 < k+b;k1++)
				    c.elem[i1][j1] += a.elem[i1][k1]*b1.elem[k1][j1];
	    break;
	case 1:
	    for(i = 0;i < a.size_x;i+=b)
		for(j = 0;j < a.size_y;j+=b)
		    for(k = 0;k < a.size_x;k+=b)
			for(int i1 = i;i1 < i+b;i1++)
			    for(int k1 = k;k1 < k+b;k1++)
				for(int j1 = j;j1 < j+b;j1++)
				    c.elem[i1][j1] += a.elem[i1][k1]*b1.elem[k1][j1];
	    break;
	case 2:
	    for(i = 0;i < a.size_x;i+=b)
		for(j = 0;j < a.size_y;j+=b)
		    for(k = 0;k < a.size_x;k+=b)
			for(int i1 = i;i1 < i+b;i1++)
			    for(int k1 = k;k1 < k+b;k1++)
				for(int j1 = j;j1 < j+b;j1++)
				    c.elem[i1][j1] += a.elem[i1][k1]*b1.elem[k1][j1];
	    break;
	case 3:
	    for(i = 0;i < a.size_x;i+=b)
		for(j = 0;j < a.size_y;j+=b)
		    for(k = 0;k < a.size_x;k+=b)
			for(int j1 = j;j1 < j+b;j1++)
			    for(int i1 = i;i1 < i+b;i1++)
				for(int k1 = k;k1 < k+b;k1++)
				    c.elem[i1][j1] += a.elem[i1][k1]*b1.elem[k1][j1];
	    break;
	case 4:
	    for(i = 0;i < a.size_x;i+=b)
		for(j = 0;j < a.size_y;j+=b)
		    for(k = 0;k < a.size_x;k+=b)
			for(int j1 = j;j1 < j+b;j1++)
			    for(int k1 = k;k1 < k+b;k1++)
				for(int i1 = i;i1 < i+b;i1++)
				    c.elem[i1][j1] += a.elem[i1][k1]*b1.elem[k1][j1];
	    break;
	case 5:
	    for(i = 0;i < a.size_x;i+=b)
		for(j = 0;j < a.size_y;j+=b)
		    for(k = 0;k < a.size_x;k+=b)
			for(int k1 = k;k1 < k+b;k1++)
			    for(int j1 = j;j1 < j+b;j1++)
				for(int i1 = i;i1 < i+b;i1++)
				    c.elem[i1][j1] += a.elem[i1][k1]*b1.elem[k1][j1];
	    break;
	default:
	    break;
    }

}
