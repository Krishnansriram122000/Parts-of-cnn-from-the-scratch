
#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>


class qwerty
{ 
	long double ***w,**hid;
	float alpha;
	int *m,*n,*z,*x;
	
	public:
	
	qwerty(int,int,int);
	void show(int,int,int);
	void mult(int,int,int);
	~qwerty()
	{ 
		delete w,m,n,z,x;
	}
};
	qwerty::qwerty(int input,int output,int hidden=1)
{ 
		alpha=0.2;
		m=new int[input];
		n=new int[output];
		w= new long double**[hidden+1];
		hid=new long double*[hidden];
		
		for(int i=0;i<hidden;i++)
		{ 
			hid[i]=new long double[input+2];
			for(int j=0;j<input+2;hid[i][j]=0,j++);
		}

		w[0]=new long double*[input];
		for(i=0;i<input;i++)
		{
			w[0][i]=new long double[input+2];
			
			for(int j=0;j<input+2;j++)
			{
				double d=random(1000000);
				w[0][i][j]=d/1000000;
			}
		}
		for(int k=1;k<hidden;k++)
		{
			w[k]=new long double*[input+2];
			for(int i=0;i<input+2;i++)
			{
				w[k][i]=new long double[input+2];
				for(int j=0;j<input+2;j++)
				{
					double d=random(1000000);
					w[k][i][j]=d/1000000;
				}
			}
		}
		w[hidden]=new long double*[input+2];
		for( i=0;i<input+2;i++)
		{
			w[hidden][i]=new long double[output];
			for(int j=0;j<input+2;j++)
			{
				double d=random(1000000);
				w[hidden][i][j]= d/1000000;
			}
		}
}
	
	
	void qwerty::mult(int input,int output,int hidden)
{
	for(int k=0;k<input+2;k++)
		for(int i=0;i<input;i++)
			hid[0][k]+=m[i]*w[0][i][k];

	for(int l=1;l<hidden;l++)
	{ for(int k=0;k<input+2;k++)
		for(int i=0;i<input+2;i++)
				hid[l][k]+=w[l][i][k]*hid[l-1][i];
	}

	for( k=0;k<output;k++)
	{
		n[k]=0;
		for(int i=0;i<input+2;i++)
		n[k]+=hid[hidden-1][i]*w[hidden][i][k];
	}
}
	void qwerty::show(int input,int output,int hidden)
{
	for(int i=0;i<input;i++)
	{
		for(int j=0;j<input+2;cout<<w[0][i][j]<<'\t',j++);
		cout<<"\n";
	}
	cout<<"\n";
    delay(5000);
	for(int k=1;k<hidden;k++)
	  {
		 for( i=0;i<input+2;i++)
			{  
				for( int j=0;j<input+2;cout<<w[k][i][j]<<'\t',j++);
				cout<<"\n";
			}
		delay(5000);
	  }

	for( i=0;i<input+2;i++)
	{
		for(int j=0;j<output;cout<<w[hidden][i][j]<<"\t",j++);
		cout<<"\n";
	}
	
}


void main()
{
	clrscr();
	qwerty u(5,3,2);
	u.mult(5,3,2);
	u.show(5,3,2);
	getch();
}

