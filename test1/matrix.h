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
char command_parser(int num,char** command);
void rff_d(char* name,mat_d& in);
void rff_f(char* name,mat_f& in);
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
						sum += a.elem[i][k]*b.elem[k][j]+2;
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
