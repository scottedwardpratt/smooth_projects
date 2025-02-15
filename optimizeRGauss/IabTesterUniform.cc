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
		Kab+=0.25*pow(theta_a-theta,2)*pow(theta_b-theta,2)*exp(-X)*dtheta;
		//Kab+=0.25*pow(pow(theta_a-theta,2)+pow(theta_b-theta,2),2)*exp(-X)*dtheta;
	}
	Iab*=0.5/beta;
	Jab*=0.5/beta;
	Kab*=0.5/beta;
}

void GetIiJiKi_analytic(double beta,double gamma,double theta_a,double theta_b,double &Iab,double &Jab,double &Kab){
	double deltheta,thetabar,rootgamma,Xplus,Xminus,X,P,Y,Z,Pprime,Pprimeprime,W,bplus2,bminus2,deltheta2,bplus,bminus;
	double gammagamma=gamma;
	rootgamma=sqrt(gammagamma);
	thetabar=0.5*(theta_a+theta_b);
	deltheta=0.5*(theta_a-theta_b);
	deltheta2=deltheta*deltheta;
	bplus=beta-thetabar;
	bminus=-beta-thetabar;
	bplus2=bplus*bplus;
	bminus2=bminus*bminus;
	Xplus=exp(-gamma*bplus2);
	Xminus=exp(-gamma*bminus2);
	P=(0.5/beta)*exp(-gamma*deltheta*deltheta);
	W=(1.0/rootgamma)*(sqrt(PI)/2.0)*(erf(rootgamma*(beta-thetabar))-erf(rootgamma*(-beta-thetabar)));
	Iab=P*W;
	
	Jab=-(0.5/gamma)*Iab-deltheta2*Iab;
	Y=bplus*Xplus-bminus*Xminus;
	Jab+=(0.5/gamma)*P*Y;

	Kab=Jab*((-0.5/gamma)-deltheta2);
	Kab+=0.5*Iab/(gamma*gamma);
	Kab=Kab-P*Xplus*bplus*((0.5/(gamma*gamma))+0.5*(deltheta2/gamma)+0.5*bplus*bplus/gamma);
	Kab=Kab+P*Xminus*bminus*((0.5/(gamma*gamma))+0.5*(deltheta2/gamma)+0.5*bminus*bminus/gamma);
	
	Kab-=Iab*(2.0*deltheta2/gamma);
	Kab=Kab+P*Xplus*bplus*2.0*deltheta2/gamma;
	Kab=Kab-P*Xminus*bminus*2.0*deltheta2/gamma;
	
	Kab=Kab/4.0;
	
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


