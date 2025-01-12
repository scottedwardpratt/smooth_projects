#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_smoothutils/log.h"

using namespace std;
int main(){
	NBandSmooth::CSmoothMaster master;
	double SigmaAbar,SigmaA,Lambdabar,Lambda,logPbar,logP;
	unsigned int iY,NObs;
	FILE *fptr=fopen("SigmaVsLambda/sigmalambda.txt","w");
	
	NObs=master.observableinfo->NObservables;
	SigmaAbar=logPbar=Lambdabar=0.0;
	
	for(iY=0;iY<NObs;iY++){
		master.emulator[iY]->CalcSigmaLambda();
		SigmaA=master.emulator[iY]->SigmaA;
		Lambda=master.emulator[iY]->LAMBDA;
		logP=master.emulator[iY]->logP;
		fprintf(fptr,"%8.2f %6.3f\n",SigmaA,Lambda);
			
		SigmaAbar+=SigmaA;
		Lambdabar+=Lambda;
		logPbar+=logP;
			
	}
	SigmaAbar=SigmaAbar/double(NObs);
	Lambdabar=Lambdabar/double(NObs);
	logPbar=logPbar/double(NObs);
	printf("<SigmaA>=%g  <Lambda>=%g <logP>=%g\n", SigmaAbar,Lambdabar,logPbar);
	fclose(fptr);
	return 0;
}
