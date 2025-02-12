#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <complex>
#include <string>
#include <cstring>
#include "msu_commonutils/randy.h"
const double PI=4.0*atan(1.0);
const double HBARC=197.3269602;

using namespace std;
using namespace NMSUPratt;


void GetIiJiKi_numerical(Crandy *randy,double beta,double gamma,double theta_a,double theta_b,double &Iab,double &Jab,double &Kab){
	double theta,X,R;
	int isample,nsample=100000000;
	Iab=Jab=Jba=Kab=0.0;
	R=1.0/sqrt(beta);
	for(isample=0;isample<nsample;isample++){
		theta=R*randy->ran_gauss();
		X=0.5*gamma*pow(theta_a-theta,2)+0.5*gamma*pow(theta_b-theta,2);
		Iab+=exp(-X);
		Jab+=pow(theta_a-theta,2)*exp(-X);
		Jba+=pow(theta_b-theta,2)*exp(-X);
		Kab+=pow(theta_a-theta,2)*pow(theta_b-theta,2)*exp(-X);
	}
	Iab=Iab/double(nsample);
	Jab=Jab/double(nsample);
	Jba=Jba/double(nsample);
	Kab=Kab/double(nsample);
}

void GetIJK_analytic(double beta,double gamma,double theta_a,double theta_b,double &Iab,double &Jab,double &Jba,double &Kab){
	double X,dXdgamma_a,dXdgamma_b,lambda,d2Xdgamma_adgamma_b;
	lambda=2.0*gamma+beta;
	X=gamma*gamma*pow(theta_a-theta_b,2)+beta*gamma*(theta_a*theta_a+theta_b*theta_b);
	Iab=sqrt(beta/lambda)*exp(-0.5*X/lambda);
	dXdgamma_a=gamma*pow(theta_a-theta_b,2)+beta*theta_a*theta_a;
	dXdgamma_b=gamma*pow(theta_a-theta_b,2)+beta*theta_b*theta_b;
	Jab=-(0.5/lambda)*Iab+(0.5*X/(lambda*lambda))*Iab-(0.5*dXdgamma_a/lambda)*Iab;
	Jba=-(0.5/lambda)*Iab+(0.5*X/(lambda*lambda))*Iab-(0.5*dXdgamma_b/lambda)*Iab;
	d2Xdgamma_adgamma_b=pow(theta_a-theta_b,2);
	Kab=Jab*Jba/Iab +(0.5/(lambda*lambda))*Iab -(X/(lambda*lambda*lambda))*Iab
	+(0.5*(dXdgamma_a+dXdgamma_b)/(lambda*lambda))*Iab -(0.5*d2Xdgamma_adgamma_b/lambda)*Iab;
	Jab*=2.0;
	Jba*=2.0;
	Kab*=4.0;
}




int main(int argc,char *argv[]){
	double Iab,Jab,Jba,Kab;
	double gamma=0.25,beta=3.0;
	double theta_a;
	double theta_b;
	Crandy *randy=new Crandy(123);

	for(int isample=0;isample<5;isample++){
		theta_a=(1.0/sqrt(beta))*randy->ran_gauss();
		theta_b=(1.0/sqrt(beta))*randy->ran_gauss();
		GetIJK_numerical(randy,beta,gamma,theta_a,theta_b,Iab,Jab,Jba,Kab);
		printf("-------------------------------------\n");
		printf("numerical: I=%8.5f J=(%8.5f,%8.5f)  K=%8.5f\n",Iab,Jab,Jba,Kab);
		GetIJK_analytic(beta,gamma,theta_a,theta_b,Iab,Jab,Jba,Kab);
		printf(" analytic: I=%8.5f J=(%8.5f,%8.5f)  K=%8.5f\n",Iab,Jab,Jba,Kab);
	}
	return 0;
}


