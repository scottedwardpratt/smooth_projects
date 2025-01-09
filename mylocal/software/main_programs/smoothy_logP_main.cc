#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_smoothutils/log.h"

using namespace std;
int main(){
	NBandSmooth::CSmoothMaster master;
	double Lambda,sigmaA,logPbar;
	unsigned int iY,NObs;
	NObs=master.observableinfo->NObservables;

	Lambda=3.0;
	for(iY=0;iY<NObs;iY++){
		master.emulator[iY]->LAMBDA=Lambda;
	}
	
	for(sigmaA=200;sigmaA<500.1;sigmaA+=10){
		logPbar=0.0;
		for(iY=0;iY<NObs;iY++){
			//master.emulator[iY]->TuneForSigmaA(sigmaA);
			master.emulator[iY]->CalcSigmaA();
			master.emulator[iY]->CalcExactLogP();
			logPbar+=master.emulator[iY]->logP;
		}
		printf("%8.2f: %g\n",sigmaA,logPbar/double(NObs));
	}
	
	return 0;
}
