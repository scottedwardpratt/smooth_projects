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

void GetIiJiKi_numerical(Crandy *randy,double beta,double Lambda,double theta_a,double theta_b,double &Iab,double &Jab,double &Kab){
	double theta,X,R,gamma=1.0/(Lambda*Lambda),Y;
	int isample,nsample=10000000;
	Iab=Jab=Kab=0.0;
	R=beta;
	for(isample=0;isample<nsample;isample++){
		theta=R*randy->ran_gauss();
		X=0.5*pow(theta_a-theta,2)+0.5*pow(theta_b-theta,2);
		Y=exp(-gamma*X);
		Iab+=Y;
		Jab+=2*X*Y;
		Kab+=pow(theta_a-theta,2)*pow(theta_b-theta,2)*Y;
	}
	Iab=Iab/double(nsample);
	Jab=Jab/double(nsample);
	Kab=Kab/double(nsample);
}

void GetIiJiKi_analytic(double beta,double Lambda,double theta_a,double theta_b,double &Iab,double &Jab,double &Kab){
	double X,gamma,alpha,lambda,deltheta2,sumt2,Jterm,Jterma,Jtermb,Kterm;
	gamma=1.0/(Lambda*Lambda);
	alpha=1.0/(beta*beta);
	lambda=2.0*gamma+alpha;
	X=gamma*gamma*pow(theta_a-theta_b,2)+alpha*gamma*(theta_a*theta_a+theta_b*theta_b);
	deltheta2=(theta_a-theta_b)*(theta_a-theta_b);
	sumt2=theta_a*theta_a+theta_b*theta_b;
	
	Iab=sqrt(alpha/lambda)*exp(-0.5*X/lambda);
	Jterm=(-1.0/lambda)
		-deltheta2*((gamma*gamma+alpha*gamma)/(lambda*lambda))
		+sumt2*(-0.5*alpha*alpha/(lambda*lambda));	
	Jterma=0.5*Jterm-0.25*(alpha/lambda)*(theta_a*theta_a-theta_b*theta_b);
	Jtermb=Jterm-Jterma;
	Jab=Iab*Jterm;
	//printf("Jterm=%g=?%g\n",Jterm,Jterma+Jtermb);
	//Kterm=Jterma*Jtermb+0.5/(lambda*lambda)
	//+(gamma*gamma-gamma*lambda)*pow(theta_a+theta_b,2)/pow(lambda,3)
	//	+theta_a*theta_b/lambda;
	//Kterm=Jterma*Jtermb+0.5/(lambda*lambda)
		//+(gamma*gamma-gamma*lambda)*(theta_a*theta_a+theta_b*theta_b)/pow(lambda,3)
		//+theta_a*theta_b*(2.0*gamma*gamma+2.0*gamma*alpha+alpha*alpha)/pow(lambda,3);
	Kterm=Jterma*Jtermb+0.5/(lambda*lambda)
		+(0.5*alpha*alpha*sumt2-0.5*(2*gamma*gamma+alpha*lambda)*deltheta2)/pow(lambda,3);
	Kab=4*Iab*Kterm;
	Jab*=-2;
}

int main(int argc,char *argv[]){
	double Iab,Jab,Jba,Kab,Lambda=2.5,dLambda=0.01;
	double beta=1.0/sqrt(3.0);
	double theta_a;
	double theta_b;
	Crandy *randy=new Crandy(123);

	for(int isample=0;isample<5;isample++){
		theta_a=(1.0/sqrt(beta))*randy->ran_gauss();
		theta_b=(1.0/sqrt(beta))*randy->ran_gauss();
		GetIiJiKi_numerical(randy,beta,Lambda,theta_a,theta_b,Iab,Jab,Kab);
		printf("-------------------------------------\n");
		printf("numerical: I=%8.5f J=%8.5f  K=%8.5f\n",Iab,Jab,Kab);
		GetIiJiKi_analytic(beta,Lambda,theta_a,theta_b,Iab,Jab,Kab);
		printf(" analytic: I=%8.5f J=%8.5f  K=%8.5f\n",Iab,Jab,Kab);
	}
	
	double Iplus,Iminus,Jplus,Jminus,I0,J0,K0,factplus,factminus,fact0;
	fact0=2.0/pow(Lambda,3);
	factplus=-2.0/pow(Lambda+0.5*dLambda,3);
	factminus=-2.0/pow(Lambda-0.5*dLambda,3);
	
	GetIiJiKi_analytic(beta,Lambda,theta_a,theta_b,I0,J0,K0);
	GetIiJiKi_analytic(beta,Lambda+0.5*dLambda,theta_a,theta_b,Iplus,Jplus,Kab);
	GetIiJiKi_analytic(beta,Lambda-0.5*dLambda,theta_a,theta_b,Iminus,Jminus,Kab);
	
	printf("dI/dLambda=%g =? %g\n",(Iplus-Iminus)/dLambda,0.5*fact0*J0);
	printf("d2I/dLambda2=%g =? %g\n",
	4.0*(Iplus-2.0*I0+Iminus)/(dLambda*dLambda),0.5*(Jplus*factplus-Jminus*factminus)/dLambda);
	
	
	return 0;
}


