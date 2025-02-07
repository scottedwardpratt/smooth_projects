#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/simplex.h"
#include "msu_smoothutils/log.h"
#include "msu_smoothutils/misc.h"
using namespace std;
using namespace NMSUUtils;
int main(){
	NBandSmooth::CSimplexSampler *simplex=new NBandSmooth::CSimplexSampler();
	double LAMBDA=3.0,ALPHA=0.0,Sigma2Bar,R=0.9,bestR,bestSigma2,dr=0.01,detB,W11;
	int imc,nmc=1000000;
	Crandy randy(123);

	//printf("Enter LAMBDA and ALPHA: ");
	//scanf("%lf %lf",&LAMBDA,&ALPHA);
	printf("Enter AlPHA: \n");
	scanf("%lf",&ALPHA);

	bestR=R;
	simplex->RGauss=R;
	simplex->SetThetaSimplex();
	Sigma2Bar=simplex->GetSigma2Bar(LAMBDA,ALPHA,detB,W11);
	bestSigma2=Sigma2Bar;
	printf("Sigma2Bar=%g, NTrain=%d\n",Sigma2Bar,int(simplex->NTrainingPts));

	for(imc=0;imc<nmc;imc++){
		R=bestR+dr*randy.ran_gauss();
		if(R<0)
			R=-R;
		simplex->RGauss=R;
		simplex->SetThetaSimplex();
		Sigma2Bar=simplex->GetSigma2Bar(LAMBDA,ALPHA,detB,W11);
		if(Sigma2Bar<bestSigma2){
			bestR=R;
			bestSigma2=Sigma2Bar;
			printf("R=%11.7f, <sigma_E^2/sigma_A^2>=%g\n",R,Sigma2Bar);
		}
		
	}
	
	return 0;
}
