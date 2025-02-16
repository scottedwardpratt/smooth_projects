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

void GetIiJiKiNumerical(Crandy *randy,double Rprior,double Lambda,double theta_a,double theta_b,double &I,double &Jaterm,double &Jbterm,double &Kabterm){
	double Ja,Jb,Kab;
	double theta,X,dtheta,Y,gamma=1.0/(Lambda*Lambda);
	int nsample=100000000;
	I=Ja=Jb=Kab=0.0;
	dtheta=2.0*Rprior/double(nsample);
	for(theta=-Rprior+0.5*dtheta;theta<Rprior;theta+=dtheta){
		X=pow(theta_a-theta,2)+pow(theta_b-theta,2);
		Y=exp(-0.5*gamma*X);
		I+=Y*dtheta;
		Ja+=pow(theta_a-theta,2)*Y*dtheta;
		Jb+=pow(theta_b-theta,2)*Y*dtheta;
		Kab+=pow(theta_a-theta,2)*pow(theta_b-theta,2)*Y*dtheta;
		//Kab+=0.25*pow(pow(theta_a-theta,2)+pow(theta_b-theta,2),2)*Y*dtheta;
	}
	I*=0.5/Rprior;
	Ja*=0.5/Rprior;
	Jb*=0.5/Rprior;
	Kab*=0.5/Rprior;
	Jaterm=Ja/I;
	Jbterm=Jb/I;
	Kabterm=Kab/I;
	printf("I=%8.5f, Jaterm=%8.5f, Jbterm=%8.5f, Sum=%8.5f, Kabterm=%8.5f\n",
	I,Jaterm,Jbterm,Jaterm+Jbterm,Kabterm);
}

void GetIiJiKiUniform(double Rprior,double Lambda,double theta_a,double theta_b,
double &I,double &Jaterm,double &Jbterm,double &Kabterm){
	double Ja,Jb,J,Kab;
	double deltheta,thetabar,rootgamma,Xplus,Xminus,P,Y,W,bplus2,bminus2,deltheta2,bplus,bminus;
	double gamma=1.0/(Lambda*Lambda);
	rootgamma=sqrt(gamma);
	thetabar=0.5*(theta_a+theta_b);
	deltheta=0.5*(theta_a-theta_b);
	deltheta2=deltheta*deltheta;
	bplus=Rprior-thetabar;
	bminus=-Rprior-thetabar;
	bplus2=bplus*bplus;
	bminus2=bminus*bminus;
	Xplus=exp(-gamma*bplus2);
	Xminus=exp(-gamma*bminus2);
	P=(0.5/Rprior)*exp(-gamma*deltheta*deltheta);
	W=(1.0/rootgamma)*(sqrt(PI)/2.0)*(erf(rootgamma*(Rprior-thetabar))-erf(rootgamma*(-Rprior-thetabar)));
	I=P*W;
	
	J=-(0.5/gamma)*I-deltheta2*I;
	Y=bplus*Xplus-bminus*Xminus;
	J+=(0.5/gamma)*P*Y;
	
	Ja=J-P*Xplus*deltheta/gamma+P*Xminus*deltheta/gamma;
	Jb=2.0*J-Ja;	

	Kab=J*((-0.5/gamma)-deltheta2);
	Kab+=0.5*I/(gamma*gamma);
	Kab=Kab-P*Xplus*bplus*((0.5/(gamma*gamma))+0.5*(deltheta2/gamma)+0.5*bplus*bplus/gamma);
	Kab=Kab+P*Xminus*bminus*((0.5/(gamma*gamma))+0.5*(deltheta2/gamma)+0.5*bminus*bminus/gamma);
	
	Kab-=I*(2.0*deltheta2/gamma);
	Kab=Kab+P*Xplus*bplus*2.0*deltheta2/gamma;
	Kab=Kab-P*Xminus*bminus*2.0*deltheta2/gamma;

	J=-2.0*J;
	Jaterm=-Ja/I;
	Jbterm=-Jb/I;
	Kabterm=Kab/I;
	printf("I=%8.5f, Jaterm=%8.5f, Jbterm=%8.5f, Sum=%8.5f, Kabterm=%8.5f\n",
	I,Jaterm,Jbterm,Jaterm+Jbterm,Kabterm);

}

int main(int argc,char *argv[]){
	double I,Jaterm,Jbterm,Kabterm,Lambda=2.5,dLambda=0.001;
	double Rprior=0.876543;
	double theta_a;
	double theta_b;
	Crandy *randy=new Crandy(123);

	for(int isample=0;isample<5;isample++){
		theta_a=(1.0/sqrt(Rprior))*randy->ran_gauss();
		theta_b=(1.0/sqrt(Rprior))*randy->ran_gauss();
		printf("-------------------------------------\n");
		GetIiJiKiNumerical(randy,Rprior,Lambda,theta_a,theta_b,I,Jaterm,Jbterm,Kabterm);
		GetIiJiKiUniform(Rprior,Lambda,theta_a,theta_b,I,Jaterm,Jbterm,Kabterm);
	}

	return 0;
}


