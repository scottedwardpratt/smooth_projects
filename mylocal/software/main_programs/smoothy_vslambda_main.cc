#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_smoothutils/log.h"

using namespace std;
int main(){
	NBandSmooth::CSmoothMaster master;
	double Lambda,sigmaAbar,logPbar,logP,sigma2,dsigma,sigmaA;
	unsigned int iY,NObs,isigma,Nsigma=100;
	vector<unsigned int> sigmadist(Nsigma);
	string filename;
	FILE *fptr1,*fptr2;
	dsigma=5.0;
	
	NObs=master.observableinfo->NObservables;

	fptr2=fopen("SigmaVsLambda/SigmaAvslambda.txt","w");
	for(Lambda=3;Lambda<3.01;Lambda+=0.25){
		for(isigma=0;isigma<Nsigma;isigma++)
			sigmadist[isigma]=0;
		filename="SigmaVsLambda/sigmadist_Lambda"+to_string(Lambda)+".txt";
		fptr1=fopen(filename.c_str(),"w");
		sigmaAbar=sigma2=logPbar=0.0;
		for(iY=0;iY<NObs;iY++){
			master.emulator[iY]->LAMBDA=Lambda;
		}
		master.TuneAllY();
		//master.TestAtTrainingPts();
		fprintf(fptr1,"%5.2f ",Lambda);
		for(iY=0;iY<NObs;iY++){
			sigmaA=master.emulator[iY]->SigmaA;
			logP=master.emulator[iY]->logP;
			sigmaAbar+=sigmaA;
			logPbar+=logP;
			sigma2+=sigmaA*sigmaA;
			isigma=lrint(sigmaA/dsigma);
			if(isigma<Nsigma){
				sigmadist[isigma]+=1;
			}
		}
		sigmaAbar=sigmaAbar/double(NObs);
		logPbar=logPbar/double(NObs);
		sigma2=sigma2/double(NObs)-sigmaAbar*sigmaAbar;
		for(isigma=0;isigma<Nsigma;isigma++){
			fprintf(fptr1,"%6.1f %u\n",isigma*dsigma,sigmadist[isigma]);
		}
		fprintf(fptr2,"%8.2f %8.2f %8.2f %8.2f\n",Lambda,logPbar,sigmaAbar,sqrt(sigma2));
		fclose(fptr1);
	}
	fclose(fptr2);
	
	return 0;
}
