#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/simplex.h"
#include "msu_smoothutils/log.h"
#include "msu_smoothutils/misc.h"
const double PI=4.0*atan(1.0);
using namespace std;
using namespace NMSUUtils;
int main(){
	NBandSmooth::CSimplexSampler *simplex=new NBandSmooth::CSimplexSampler();
	double LAMBDA=3.0,ALPHA=0.01,Sigma2Bar,bestSigma2,dtheta=0.05,detB,W11,r;
	int imc,nmc=10000000,itrain,NPars,NTrain,ipar,nfail=0;
	Crandy randy(time(NULL));
	vector<vector<double>> besttheta;
	NPars=simplex->NPars;

	//printf("Enter LAMBDA and ALPHA: ");
	//scanf("%lf %lf",&LAMBDA,&ALPHA);
	
	/*
	double R1=0.9021,R2=1.312;
	simplex->RGauss1=R1;
	simplex->RGauss2=R2;
	simplex->SetThetaSimplex();
	NTrain=simplex->NTrainingPts;
	besttheta.resize(NTrain);
	for(itrain=0;itrain<NTrain;itrain++){
		besttheta[itrain].resize(NPars);
		for(ipar=0;ipar<NPars;ipar++){
			besttheta[itrain][ipar]=simplex->ThetaTrain[itrain][ipar];
			simplex->ThetaTrain[itrain][ipar]=besttheta[itrain][ipar];
		}
	}
	*/
	
	double R0=1.0/sqrt(3.0);
	printf("Enter NTrainingPts: ");
	scanf("%d",&NTrain);
	besttheta.resize(NTrain);
	for(itrain=0;itrain<NTrain;itrain++){
		besttheta[itrain].resize(NPars);
		for(ipar=0;ipar<NPars;ipar++){
			besttheta[itrain][ipar]=R0*randy.ran_gauss();
			if(itrain==0)
				besttheta[itrain][ipar]=0.0;
			if(itrain==1 && ipar!=0){
				besttheta[itrain][ipar]=0.0;
			}
		}
	}
	simplex->SetThetaTrain(besttheta);
	
	Sigma2Bar=simplex->GetSigma2Bar(LAMBDA,ALPHA,detB,W11);
	bestSigma2=Sigma2Bar;
	/*
	for(itrain=0;itrain<NTrain;itrain++){
		r=0.0;
		printf("%2d: ",itrain);
		for(ipar=0;ipar<NPars;ipar++){
			r+=pow(besttheta[itrain][ipar],2);
			printf("%8.5f ",besttheta[itrain][ipar]);
		}
		printf(": %8.5f\n",sqrt(r));
	}*/
	
	for(imc=0;imc<nmc;imc++){
		for(itrain=0;itrain<NTrain;itrain++){
			for(ipar=0;ipar<NPars;ipar++){
				simplex->ThetaTrain[itrain][ipar]=besttheta[itrain][ipar]+dtheta*randy.ran_gauss();
				if(itrain==0){
					simplex->ThetaTrain[itrain][ipar]=0.0;
				}
				if(itrain==1 && ipar!=0){
					simplex->ThetaTrain[itrain][ipar]=0.0;
				}
					
			}
		}
		Sigma2Bar=simplex->GetSigma2Bar(LAMBDA,ALPHA,detB,W11);
		if(Sigma2Bar<bestSigma2){
			bestSigma2=Sigma2Bar;
			//printf("bestSigma2=%g, detB=%g\n",bestSigma2,detB);
			for(itrain=0;itrain<NTrain;itrain++){
				for(ipar=0;ipar<NPars;ipar++){
					besttheta[itrain][ipar]=simplex->ThetaTrain[itrain][ipar];
				}
			}
			nfail=0;
		}
		else
			nfail+=1;
		if(nfail>100){
			//dtheta*=0.75;
			nfail=0;
		}
		if((10*(imc+1)%nmc)==0){
			printf("++++++++++++++++++++finished %g percent +++++++++++++++++++++++\n",100.0*(imc+1.0)/double(nmc));
			dtheta*=0.5;
		}
		
	}
	printf("--- best Sigma2=%g ---\n",bestSigma2);
	for(itrain=0;itrain<NTrain;itrain++){
		r=0.0;
		printf("%2d: ",itrain);
		for(ipar=0;ipar<NPars;ipar++){
			r+=pow(besttheta[itrain][ipar],2);
			printf("%8.5f ",besttheta[itrain][ipar]);
		}
		printf(": %8.5f\n",sqrt(r));
		
	}
	FILE *fptr=fopen("Sigma2vsNTrain.txt","a");
	fprintf(fptr,"%3d %8.5f\n",NTrain,bestSigma2);
	fclose(fptr);
	
	fptr=fopen("ctheta.txt","w");
	double ctheta;
	int jtrain;
	vector<double> rtrain(NTrain);
	for(itrain=0;itrain<NTrain;itrain++){
		rtrain[itrain]=0.0;
		for(ipar=0;ipar<NPars;ipar++){
			rtrain[itrain]+=besttheta[itrain][ipar]*besttheta[itrain][ipar];
		}
		rtrain[itrain]=sqrt(rtrain[itrain]);
	}
	vector<double> sumtheta(NPars);
	for(ipar=0;ipar<NPars;ipar++)
		sumtheta[ipar]=0.0;
	for(itrain=0;itrain<NTrain;itrain++){
		for(ipar=0;ipar<NPars;ipar++){
			sumtheta[ipar]+=besttheta[itrain][ipar];
		}
		for(jtrain=0;jtrain<NTrain;jtrain++){
			double rij=0.0;
			if(rtrain[itrain]>0.1 && rtrain[jtrain]>0.1){
				ctheta=0.0;
				for(ipar=0;ipar<NPars;ipar++){
					rij+=pow(besttheta[itrain][ipar]-besttheta[jtrain][ipar],2);
					ctheta+=besttheta[itrain][ipar]*besttheta[jtrain][ipar];
				}
				rij=sqrt(rij);
				ctheta=ctheta/(rtrain[itrain]*rtrain[jtrain]);
				fprintf(fptr,"%8.5f ",ctheta);
				if(fabs(ctheta-0.6)<0.03)
					printf("rij=%g\n",rij);
			}
		}
		fprintf(fptr,"\n");
	}			
	fclose(fptr);
	
	for(ipar=0;ipar<NPars;ipar++){
		printf("sumtheta[%d]=%g\n",ipar,sumtheta[ipar]);
	}
	vector<double> phi(NTrain),theta(NTrain);
	for(itrain=0;itrain<NTrain;itrain++){
		ctheta=besttheta[itrain][0];
		r=0.0;
		for(ipar=0;ipar<NPars;ipar++){
			r+=besttheta[itrain][ipar]*besttheta[itrain][ipar];
		}
		r=sqrt(r);
		ctheta=ctheta/r;
		phi(NTrain)=atan2(besttheta[itrain][2],besttheta[itrain][1]);
		if(theta<0.0)
			theta+=PI;
		theta(NTrain)=(180.0/PI)*acos(ctheta);
		phi(NTrain)=(180.0/PI)*phi(NTrain);
		printf("%8.5f %9.3f %9.3f\n",r,theta,phi);
	}
	return 0;
}
