#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/simplex.h"
#include "msu_smoothutils/log.h"
#include "msu_smoothutils/misc.h"
using namespace std;
using namespace NMSUUtils;
int main(){
	NBandSmooth::CSimplexSampler *simplex=new NBandSmooth::CSimplexSampler();
	double LAMBDA=3.0,ALPHA=0.0,Sigma2Bar,R1=0.8,R2=1.4,bestR1,bestR2,bestSigma2,bestdetB=-100.0,dr=0.005,detB,W11;
	int imc,nmc=10000;
	Crandy randy(123);

	printf("Enter LAMBDA & AlPHA: \n");
	scanf("%lf %lf",&LAMBDA,&ALPHA);

	bestR1=R1;
	bestR2=R2;
	simplex->RGauss1=R1;
	simplex->RGauss2=R2;
	simplex->SetThetaSimplex();
	Sigma2Bar=simplex->GetSigma2Bar(LAMBDA,ALPHA,detB,W11);
	//detB=detB*pow(exp(-1.5*R1*R1),NPars+1)*pow(exp(-1.5*R2*R2),NTrain-NPars-1);
	
	bestSigma2=Sigma2Bar;
	printf("Sigma2Bar=%g, detB=%g, W11=%g, NPars=%d, NTrain=%d\n",
	Sigma2Bar,detB,W11,int(simplex->NPars),int(simplex->NTrainingPts));

	for(imc=0;imc<nmc;imc++){
		R1=bestR1+dr*randy.ran_gauss();
		if(R1<0)
			R1=-R1;
		R2=bestR2+dr*randy.ran_gauss();
		if(R2<0)
			R2=-R2;
		simplex->RGauss1=R1;
		simplex->RGauss2=R2;
		simplex->SetThetaSimplex();
		Sigma2Bar=simplex->GetSigma2Bar(LAMBDA,ALPHA,detB,W11);
		//detB=detB*pow(exp(-1.5*R1*R1),NPars+1)*pow(exp(-1.5*R2*R2),NTrain-NPars-1);
		if(Sigma2Bar<bestSigma2){
		//if(detB>bestdetB){
			bestR1=R1;
			bestR2=R2;
			bestSigma2=Sigma2Bar;
			bestdetB=detB;
			printf("(R1,R2)=(%8.4f,%8.4f), |B|=%10.3e, W11=%10.3e , <sigma_E^2/sigma_A^2>=%g\n",
			R1,R2,detB,W11,Sigma2Bar);
		}
		
	}
	
	return 0;
}
