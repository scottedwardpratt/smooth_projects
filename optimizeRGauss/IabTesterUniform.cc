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


void GetIiJiKi_numerical(double beta,double gamma,double theta_a,double theta_b,double &Iab,double &Jab,double &Kab){
	double theta,X,R,dtheta;
	int isample,nsample=100000000;
	Iab=Jab=Kab=0.0;
	dtheta=2.0*beta/double(nsample);
	for(theta=-beta+0.5*dtheta;theta<beta;theta+=dtheta){
		X=0.5*gamma*pow(theta_a-theta,2)+0.5*gamma*pow(theta_b-theta,2);
		Iab+=exp(-X)*dtheta;
		Jab-=0.5*(pow(theta_a-theta,2)+pow(theta_b-theta,2))*exp(-X)*dtheta;
		Kab+=0.25*pow(pow(theta_a-theta,2)+pow(theta_b-theta,2),2)*exp(-X)*dtheta;
	}
	Iab*=0.5/beta;
	Jab*=0.5/beta;
	Kab*=0.5/beta;
}

void GetIiJiKi_analytic(double beta,double gamma,double theta_a,double theta_b,double &Iab,double &Jab,double &Kab){
	double deltheta,thetabar,rootgamma,Xplus,Xminus,prefact,Y,Z;
	double gammagamma=gamma;
	rootgamma=sqrt(gammagamma);
	thetabar=0.5*(theta_a+theta_b);
	deltheta=theta_a-theta_b;
	Xplus=exp(-gamma*(beta-thetabar)*(beta-thetabar));
	Xminus=exp(-gamma*(-beta-thetabar)*(-beta-thetabar));
	prefact=exp(-0.25*gamma*deltheta*deltheta);
	Iab=(0.25/beta)*sqrt(PI/gamma)*prefact*(erf(rootgamma*(beta-thetabar))-erf(rootgamma*(-beta-thetabar)));
	Jab=-(0.5/gamma)*Iab-0.25*deltheta*deltheta*Iab;
	Y=(beta-thetabar)*Xplus-(-beta-thetabar)*Xminus;
	Jab+=(0.25/(gamma*beta))*prefact*Y;
	Z=pow(beta-thetabar,3)*Xplus-pow(-beta-thetabar,3)*Xminus;
	
	
	Kab=(0.5/(gamma*gamma))*Iab
		+(-(0.5/gamma)-0.25*deltheta*deltheta)*Jab
		-((0.25/(gamma*gamma*beta)) +deltheta*deltheta/(16.0*beta*gamma))*prefact*Y	
			-(0.25/(beta*gamma))*prefact*Z;
}

int main(int argc,char *argv[]){
	double Iab,Jab,Jba,Kab;
	double gamma=0.33333333333333,beta=2.5;
	double theta_a;
	double theta_b;
	Crandy *randy=new Crandy(123);

	for(int isample=0;isample<5;isample++){
		theta_a=(1.0/sqrt(beta))*randy->ran_gauss();
		theta_b=(1.0/sqrt(beta))*randy->ran_gauss();
		GetIiJiKi_numerical(beta,gamma,theta_a,theta_b,Iab,Jab,Kab);
		printf("-------------------------------------\n");
		printf("numerical: I=%8.5f J=%8.5f  K=%8.5f\n",Iab,Jab,Kab);
		GetIiJiKi_analytic(beta,gamma,theta_a,theta_b,Iab,Jab,Kab);
		printf(" analytic: I=%8.5f J=%8.5f  K=%8.5f\n",Iab,Jab,Kab);
	}
	
	double dgamma=0.001,Iplus,Iminus,Jplus,Jminus,I0,J0,K0;
	
	GetIiJiKi_analytic(beta,gamma,theta_a,theta_b,I0,J0,K0);
	GetIiJiKi_analytic(beta,gamma+0.5*dgamma,theta_a,theta_b,Iplus,Jplus,Kab);
	GetIiJiKi_analytic(beta,gamma-0.5*dgamma,theta_a,theta_b,Iminus,Jminus,Kab);
	
	printf("dI/dgamma=%g =? %g\n",(Iplus-Iminus)/dgamma,J0);
	printf("d2I/dgamma2=%g =? %g =? %g\n",4.0*(Iplus-2.0*I0+Iminus)/(dgamma*dgamma),(Jplus-Jminus)/dgamma,K0);
	
	
	return 0;
}


