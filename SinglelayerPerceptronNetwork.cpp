#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
void main()
{ clrscr();
  int i,j,k;
  long  double  weight[]={0.7,0.2,-0.5,-0.35,0.32,-0.78},sum1=0,delta1,alpha=0.1;
  long double  data[6][3]={{1,10,0},{0,4,1},{0,18,0},{1,2,1},{0,12,1},{1,2,0}};
  long double  target[]={5,2,9,1,6,1};
  for(k=0;k<480;k++){
    for(i=0;i<6;i++){
	for(j=0;j<3;j++)
	{     //	cout<<data[i][j]<<'\t'<<weight[j]<<'\t';
		sum1+=data[i][j]*weight[j];}
	delta1=sum1-target[i];
	for(j=0;j<3;j++)
		{if(data[i][j]>0)
		weight[j]-=alpha*delta1;    }

	cout<<"predic"<<i<<"\t"<<sum1<<"\t"<<"\n";
	sum1=0;
	}
	cout<<"\n";
 //   cout<<"error==:"<<delta*delta<<"\n";
}
 
 
 //Prediction or testing the linear regression model
 
 int g[3];
 cin>>g[0]>>g[1]>>g[2];

	for(j=0;j<3;j++)
	{     //	cout<<data[i][j]<<'\t'<<weight[j]<<'\t';
		sum1+=g[j]*weight[j];}

	cout<<"predic"<<"\t"<<sum1<<"\n";
	sum1=0;


  getch();
  }
//thus our linear regression model learns from the data set and predicts the output.
