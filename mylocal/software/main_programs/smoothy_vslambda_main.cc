#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_smoothutils/log.h"

using namespace std;
int main(){
	NBandSmooth::CSmoothMaster master;
	double Lambda,sigmaAbar,Lambdabar,LambdaGuess,logPbar,logP,sigma2,dsigma,sigmaA;
	unsigned int iY,NObs,isigma,Nsigma=100;
	vector<unsigned int> sigmadist(Nsigma);
	string filename;
	FILE *fptr1,*fptr2;//*fptr3;
	dsigma=5.0;
	
	NObs=master.observableinfo->NObservables;

	fptr2=fopen("SigmaVsLambda/SigmaAvslambda.txt","w");
	//printf("Enter Lambda: ");
	//scanf("%lf",&Lambda);
	for(Lambda=1.5;Lambda<6.501;Lambda+=0.5){
		for(isigma=0;isigma<Nsigma;isigma++)
			sigmadist[isigma]=0;
		std::string Lstr = std::to_string (Lambda);
		Lstr.erase ( Lstr.find_last_not_of('0') + 1, std::string::npos );
		Lstr.erase ( Lstr.find_last_not_of('.') + 1, std::string::npos );
		filename="SigmaVsLambda/sigmadist_Lambda"+Lstr+".txt";
		fptr1=fopen(filename.c_str(),"w");
		//filename="SigmaVsLambda/sig123_"+Lstr+".txt";
		//fptr3=fopen(filename.c_str(),"w");
		
		sigmaAbar=sigma2=logPbar=Lambdabar=0.0;
		for(iY=0;iY<NObs;iY++){
			master.emulator[iY]->LAMBDA=Lambda;
			master.emulator[iY]->Bcalculated=false;
		}
		master.TuneAllY();
		//master.TestAtTrainingPts();
		fprintf(fptr1,"#Lambda=%5.2f, dsigma=%g\n",Lambda,dsigma);
		fprintf(fptr1,"#Sigma   Ndist(Sigma)\n");
		for(iY=0;iY<NObs;iY++){
			//master.emulator[iY]->CalcSigmaLambda(LambdaGuess);
			sigmaA=master.emulator[iY]->SigmaA;
			master.emulator[iY]->CalcExactLogP();
			LambdaGuess=Lambda;
			logP=master.emulator[iY]->logP;
			sigmaAbar+=sigmaA;
			logPbar+=logP;
			sigma2+=sigmaA*sigmaA;
			Lambdabar+=LambdaGuess;
			isigma=lrint(sigmaA/dsigma);
			if(isigma<Nsigma){
				sigmadist[isigma]+=1;
			}
			//fprintf(fptr3,"%8.3f %8.3f %8.3f\n",sig1,sig2,sig3);
		}
		sigmaAbar=sigmaAbar/double(NObs);
		Lambdabar=Lambdabar/double(NObs);
		logPbar=logPbar/double(NObs);
		printf("%g: <sigmaA>=%g  <Lambda>=%g <logP>=%g\n",Lambda,sigmaAbar,Lambdabar,logPbar);
		sigma2=sigma2/double(NObs)-sigmaAbar*sigmaAbar;
		for(isigma=0;isigma<Nsigma;isigma++){
			fprintf(fptr1,"%6.1f %u\n",isigma*dsigma,sigmadist[isigma]);
		}
		fprintf(fptr2,"%8.2f %8.2f %8.2f %8.2f\n",Lambdabar,logPbar,sigmaAbar,sqrt(sigma2));
		fclose(fptr1);
		//fclose(fptr3);
	}
	fclose(fptr2);
	
	return 0;
}
