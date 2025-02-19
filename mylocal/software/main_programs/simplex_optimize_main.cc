#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/simplex.h"
#include "msu_smoothutils/log.h"
#include "msu_smoothutils/misc.h"
using namespace std;
using namespace NMSUUtils;
int main(){
	double LAMBDA,ALPHA;
	int NTrain;
	NBandSmooth::CSimplexSampler *simplex=new NBandSmooth::CSimplexSampler();
	FILE *fptr=fopen("LambdaAlpha.txt","r");
	//printf("Enter Estimate for LAMBDA and ALPHA: ");
	//scanf("%lf %lf",&LAMBDA,&ALPHA);
	fscanf(fptr,"%lf %lf %d",&LAMBDA,&ALPHA,&NTrain);
	simplex->NTrainingPts=NTrain;
	simplex->Optimize(LAMBDA,ALPHA);
	//simplex->WriteModelPars();
	fclose(fptr);
	return 0;
}
