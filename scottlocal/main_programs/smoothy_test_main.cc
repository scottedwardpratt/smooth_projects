#include "msu_commonutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_commonutils/log.h"

using namespace std;
using namespace NBandSmooth;
using namespace NMSUPratt;

int main(){
	unsigned int maxrank=4;
	unsigned int npars=14;
	unsigned int ic,itheta,idtheta;
	CSmooth *smoothy=new CSmooth(npars,maxrank);
	unsigned int Ncoefficients=smoothy->NCoefficients;
	double Y,Y0,Y1,Y2,lambda=2.5,dtheta=0.01,error;
	vector<double> A(Ncoefficients),dYdTheta(Ncoefficients);
	vector<double> theta(npars),theta1(npars),theta2(npars);
	Crandy *randy=new Crandy(1234);
	
	error=0.0;
	for(int itrial=0;itrial<10000;itrial++){
		for(ic=0;ic<Ncoefficients;ic++){
			A[ic]=100.0*randy->ran();
		}
	
		for(itheta=0;itheta<npars;itheta++){
			theta[itheta]=-1.0+2.0*randy->ran();
		}
		Y=smoothy->CalcY(A,lambda,theta);
		
		Y0=Y;
		smoothy->CalcYDYDTheta(A,lambda,theta,Y,dYdTheta);
		
		error=fabs(Y0-Y);
		for(idtheta=0;idtheta<npars;idtheta++){
			for(itheta=0;itheta<npars;itheta++){
				theta1[itheta]=theta[itheta];
				theta2[itheta]=theta[itheta];
				if(itheta==idtheta){
					theta1[itheta]-=0.5*dtheta;
					theta2[itheta]+=0.5*dtheta;
				}
			}
			Y2=smoothy->CalcY(A,lambda,theta2);
			Y1=smoothy->CalcY(A,lambda,theta1);
			//printf("%g =? %g\n",dYdTheta[idtheta],(Y2-Y1)/dtheta);
			error+=fabs(dYdTheta[idtheta]-(Y2-Y1)/dtheta);
		}
		if((itrial+1)%1000==0){
			printf("net error = %9.3e\n",error);
			error=0.0;
		}
		
		
	}
	return 0;
}
