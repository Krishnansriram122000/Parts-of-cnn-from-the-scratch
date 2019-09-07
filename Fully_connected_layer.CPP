
#include<iostream>
#include<stdlib.h>
#include<dos.h>
#include<math.h>
using namespace std;
long double activate(long double x){
	return 1/(1+exp(-x));
}
class qwerty
{ 
	long double ***w,***b,**hid,**err;
	float alpha;
	long double *m,*n,**bias,**nbias,*oerr,*target;
	int input,hidden,output;
	public:
	
	qwerty(int,int,int);
	void show();
	void mult();
	void backpropagate();
	void hidanderr();
	~qwerty()
	{ 
		delete w,m,n,b,err,hid,bias,nbias,oerr;
	}
};
	qwerty::qwerty(int in,int out,int hi1=1)
{ 		
		srand(123);
		alpha=0.2;
		input=in;
		output=out;
		hidden=hi1;
		m=new long double[input];
		n=new long double[output];
		oerr=new long double[output];
		target=new long double[output];
		w= new long double**[hidden+1];
		b= new long double**[hidden+1];
		bias=new long double*[hidden+1];
		nbias=new long double*[hidden+1];
		hid=new long double*[hidden];
		err=new long double*[hidden];
		
		for(int i=0;i<hidden;i++)
		{ 
			hid[i]=new long double[input+2];
			err[i]=new long double[input+2];
			bias[i]=new long double[input+2];
			nbias[i]=new long double[input+2];
			for(int j=0;j<input+2;j++){
				hid[i][j]=err[i][j]=nbias[i][j]=0;
				double d=rand();
				bias[i][j]=(d/100000);
			}
		}
		bias[hidden]=new long double[output];
		for(int i=0;i<output;i++)
			{double d=rand();
			bias[hidden][i]=(d/100000);}
		nbias[hidden]=new long double[output];
		
		w[0]=new long double*[input];
		b[0]=new long double*[input];
		for(int i=0;i<input;i++)
		{
			w[0][i]=new long double[input+2];
			b[0][i]=new long double[input+2];
			for(int j=0;j<input+2;j++)
			{
				double d=rand();
				w[0][i][j]=((d/100000));
				b[0][i][j]=0;
			}
		}
		for(int k=1;k<hidden;k++)
		{
			w[k]=new long double*[input+2];
			b[k]=new long double*[input+2];
			for(int i=0;i<input+2;i++)
			{
				w[k][i]=new long double[input+2];
				b[k][i]=new long double[input+2];
				for(int j=0;j<input+2;j++)
				{
					double d=rand();
					w[k][i][j]=((d/100000));
					b[k][i][j]=0;
				}
			}
		}
		
		w[hidden]=new long double*[input+2];
		b[hidden]=new long double*[input+2];
		for(int i=0;i<input+2;i++)
		{
			w[hidden][i]=new long double[output];
			b[hidden][i]=new long double[output];
			for(int j=0;j<output;j++)
			{
				double d=rand();
				w[hidden][i][j]= ((d/100000));
				b[hidden][i][j]=0;
			}
		}
		
		
}
	void qwerty::hidanderr(){
		cout<<"hidden:\n";
		for(int i=0;i<hidden;cout<<"\n",i++)
			for(int j=0;j<input+2;cout<<hid[i][j]<<"\t",j++);
		cout<<"\n\nerror\n";
		for(int i=0;i<hidden;cout<<"\n",i++)
			for(int j=0;j<input+2;cout<<err[i][j]<<"\t",j++);
		cout<<"\n";
	}	
	
	void qwerty::mult()
{	
	for(int k=0;k<input+2;k++)
	{	for(int i=0;i<input;i++)
			hid[0][k]+=m[i]*w[0][i][k];
		hid[0][k]+=bias[0][k];
		hid[0][k]=activate(hid[0][k]);
	}

	for(int l=1;l<hidden;l++)
	{ for(int k=0;k<input+2;k++)
		{for(int i=0;i<input+2;i++)
			hid[l][k]+=w[l][i][k]*hid[l-1][i];
		hid[l][k]+=bias[l][k];
		hid[l][k]=activate(hid[0][k]);}
	}

	for( int k=0;k<output;k++)
	{
		n[k]=0;
		{for(int i=0;i<input+2;i++)
			n[k]+=hid[hidden-1][i]*w[hidden][i][k];
		n[k]+=bias[hidden][k];
		n[k]=activate(n[k]);}
	}
}
	void qwerty::show()
{	
	for(int i=0;i<hidden+1;i++)
		{for(int j=0;j<input+2;j++)
			{for(int k=0;k<input+2;k++)
			{
				if(i==0 && j>=input) break;
				if(i==hidden && k>=output)break;
				cout<<w[i][j][k]<<"\t";
			}
			cout<<"\n";}
		cout<<"\n\n";}
	cout<<"Biases\n";
	for(int i=0;i<hidden;i++)
		{for(int j=0;j<input+2;j++)
			cout<<bias[i][j]<<"\t";
		cout<<'\n';}
	for(int i=0;i<output;i++)cout<<bias[hidden][i]<<'\t';
	cout<<"\n";
	for(int i=0;i<hidden+1;i++)
		{for(int j=0;j<input+2;j++)
			{for(int k=0;k<input+2;k++)
			{
				if(i==0 && j>=input) break;
				if(i==hidden && k>=output)break;
				cout<<b[i][j][k]<<"\t";
			}
			cout<<"\n";}
		cout<<"\n\n";}
	cout<<"Change in Biases\n";
	for(int i=0;i<hidden;i++)
		{for(int j=0;j<input+2;j++)
			cout<<nbias[i][j]<<"\t";
		cout<<'\n';}
	for(int i=0;i<output;i++)cout<<nbias[hidden][i]<<'\t';
}
void qwerty::backpropagate(){
	//error in output layer
	for(int i=0;i<output;i++)
		oerr[i]=(target[i]-n[i])*activate(n[i])*(1-activate(n[i]));
	//change in weight in the last matrix
	for(int i=0;i<output;i++)
		{for(int j=0;j<input+2;j++)
			b[hidden][j][i]=alpha*oerr[i]*hid[hidden-1][j];
		nbias[hidden][i]=alpha*(oerr[i]);}
	//error of the penultimate layer
	for(int i=0;i<input+2;i++)
		{
		err[hidden-1][i]=0;
		for(int j=0;j<output;j++)
			err[hidden-1][i]+=oerr[j]*w[hidden][i][j];
		err[hidden-1][i]*=activate(hid[hidden-1][i])*(1-activate(hid[hidden-1][i]));
		}
	//error and weight change for all layer but input layer
	for(int i=hidden-1;i>0;i--)
	{
		for(int j=0;j<input+2;j++)
			{for(int k=0;k<input+2;k++)
				b[i][k][j]=alpha*err[i][j]*hid[i-1][k];
			nbias[i][j]=alpha*err[i][j];
			err[i-1][j]=0;
			for(int k=0;k<input+2;k++)
				err[i-1][j]+=err[i][k]*w[i][j][k];
			err[i-1][j]*=activate(hid[i-1][j])*(1-activate(hid[i-1][j]));
			}
	}
	//change in weight for 0th layer
	for(int i=0;i<input+2;i++)
		{for(int j=0;j<input;j++)
			b[0][j][i]=alpha*err[0][i]*m[j];
		nbias[0][i]=alpha*(err[0][i]);
		}

	//update biases and weights pending... 
	for(int i=0;i<hidden+1;i++)
		for(int j=0;j<input+2;j++)
			for(int k=0;k<input+2;k++)
			{
				if(i==0 && j>=input) break;
				if(i==hidden && k>=output)break;
				w[i][j][k]+=b[i][j][k];
			}
	for(int i=0;i<hidden;i++)
		for(int j=0;j<input+2;j++)
			bias[i][j]+=nbias[i][j];
	for(int i=0;i<output;i++)
		bias[hidden][i]+=nbias[hidden][i];
		
}

int main()
{
	qwerty u(2,4,3);
	//u.hidanderr();
	u.mult();
	u.show();
	//u.backpropagate();
	
	
}

