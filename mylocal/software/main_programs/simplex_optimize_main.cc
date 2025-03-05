#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/simplex.h"
#include "msu_smoothutils/log.h"
#include "msu_smoothutils/misc.h"
using namespace std;
using namespace NMSUUtils;
int main(){
	double LAMBDA=2.5,ALPHA=0.01;
	//long long int NTrain,NMC=100000;
	NBandSmooth::CSimplexSampler *simplex=new NBandSmooth::CSimplexSampler();
	FILE *fptr=fopen("LambdaAlpha.txt","r");
	//printf("Enter Estimate for LAMBDA and ALPHA: ");
	//scanf("%lf %lf",&LAMBDA,&ALPHA);
	//fscanf(fptr,"%lf %lf %lld",&LAMBDA,&ALPHA,&NTrain);
	//simplex->NMC=NMC;
	//for(LAMBDA=2.0;LAMBDA<5.01;LAMBDA+=0.25){
		simplex->Optimize(LAMBDA,ALPHA);
		//}
		simplex->WriteModelPars();
	fclose(fptr);
	return 0;
}
