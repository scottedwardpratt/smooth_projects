#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <complex>
#include <string>
#include <cstring>
#include "msu_commonutils/randy.h"
const double PI=4.0*atan(1.0);

using namespace std;
using namespace NMSUPratt;

void GetIiJiKiNumerical(Crandy *randy,double Rprior,double Lambda,double theta_a,double theta_b,
double &I,double &Jaterm,double &Jbterm,double &Kabterm){
	double theta,X,R,gamma=1.0/(Lambda*Lambda),Y;
	double Ja,Jb,Jab,Kab;
	int isample,nsample=10000000;
	I=Ja=Jb=Jab=Kab=0.0;
	for(isample=0;isample<nsample;isample++){
		theta=Rprior*randy->ran_gauss();
		X=0.5*pow(theta_a-theta,2)+0.5*pow(theta_b-theta,2);
		Y=exp(-gamma*X);
		I+=Y;
		Jab+=2*X*Y;
		Ja+=pow(theta_a-theta,2)*Y;
		Jb+=pow(theta_b-theta,2)*Y;
		Kab+=pow(theta_a-theta,2)*pow(theta_b-theta,2)*Y;
	}
	I=I/double(nsample);
	Jab=Jab/double(nsample);
	Ja=Ja/double(nsample);
	Jb=Jb/double(nsample);
	Kab=Kab/double(nsample);
	Jaterm=Ja/I;
	Jbterm=Jb/I;
	Kabterm=Kab/I;
	printf("I=%8.5f, Jaterm=%8.5f, Jbterm=%8.5f, Sum=%8.5f, Kabterm=%8.5f\n",I,Jaterm,Jbterm,Jaterm+Jbterm,Kabterm);
}

void GetIiJiKiGaussian(double Rprior,double Lambda,double theta_a,double theta_b,
double &I,double &Jaterm,double &Jbterm,double &Kabterm){
	double X,gamma,alpha,lambda,deltheta2,sumt2,Jterm;
	gamma=1.0/(Lambda*Lambda);
	alpha=1.0/(Rprior*Rprior);
	lambda=2.0*gamma+alpha;
	X=gamma*gamma*pow(theta_a-theta_b,2)+alpha*gamma*(theta_a*theta_a+theta_b*theta_b);
	deltheta2=(theta_a-theta_b)*(theta_a-theta_b);
	sumt2=theta_a*theta_a+theta_b*theta_b;
	
	I=sqrt(alpha/lambda)*exp(-0.5*X/lambda);
	Jterm=(-1.0/lambda)
		-deltheta2*((gamma*gamma+alpha*gamma)/(lambda*lambda))
		+sumt2*(-0.5*alpha*alpha/(lambda*lambda));	
	Jaterm=0.5*Jterm-0.25*(alpha/lambda)*(theta_a*theta_a-theta_b*theta_b);
	Jbterm=Jterm-Jaterm;
	//Jab=I*Jterm;
	Kabterm=Jaterm*Jbterm+0.5/(lambda*lambda)
		+(0.5*alpha*alpha*sumt2-0.5*(2*gamma*gamma+alpha*lambda)*deltheta2)/pow(lambda,3);
	Kabterm*=4;
	//Kab=4*I*Kterm;
	//Jab*=-2;
	Jaterm*=-2;
	Jbterm*=-2;
	printf("I=%8.5f, Jaterm=%8.5f, Jbterm=%8.5f, Sum=%8.5f, Kabterm=%8.5f\n",I,Jaterm,Jbterm,Jaterm+Jbterm,Kabterm);
}

int main(int argc,char *argv[]){
	double I,Jaterm,Jbterm,Kabterm,Lambda=2.5,dLambda=0.01;
	double Rprior=1.0/sqrt(3.0);
	double theta_a;
	double theta_b;
	Crandy *randy=new Crandy(123);

	for(int isample=0;isample<5;isample++){
		theta_a=Rprior*randy->ran_gauss();
		theta_b=Rprior*randy->ran_gauss();
		printf("-------------------------------------\n");
		GetIiJiKiNumerical(randy,Rprior,Lambda,theta_a,theta_b,I,Jaterm,Jbterm,Kabterm);
		GetIiJiKiGaussian(Rprior,Lambda,theta_a,theta_b,I,Jaterm,Jbterm,Kabterm);
	}
	
	return 0;
}


