#include "msu_commonutils/parametermap.h"
#include "msu_smooth/smooth.h"
#include "msu_commonutils/log.h"

using namespace std;
int main(){

	const int NObs=10,NPars=10,NTrain=66;
	unsigned int itrain,iobs,ic,ipar,maxrank=5,it=time(NULL),itest;
	double LAMBDA;
	double y,x;
	vector<double> A;
	vector<double> theta;
	vector<vector<double>> thetatest;
	theta.resize(NPars);
	NMSUPratt::Crandy randy(0);
	
	printf("Enter LAMBDA: ");
	scanf("%lf",&LAMBDA);
	
	NBandSmooth::CSmooth smooth(NPars,maxrank);
	A.resize(smooth.NCoefficients);
	
	string obsname[NObs];
	for(iobs=0;iobs<NObs;iobs++){
		obsname[iobs]="obs"+to_string(iobs+1);
	}
	string parname[NPars];
	char parname_c[200];
	string filename;
	FILE *fptr,*fptr_out;
	
	thetatest.resize(100);
	for(itest=0;itest<100;itest++){
		thetatest[itest].resize(NPars);
		for(ipar=0;ipar<NPars;ipar++){
			thetatest[itest][ipar]=-1.0+2.0*randy.ran();
		}
	}
	
	for(iobs=0;iobs<NObs;iobs++){
		randy.reset(iobs+it);
		for(ic=0;ic<smooth.NCoefficients;ic++){
			A[ic]=100.0*randy.ran_gauss();
		}
		for(itrain=0;itrain<NTrain;itrain++){
			filename="modelruns/run"+to_string(itrain)+"/mod_parameters.txt";
			//printf("filename=%s\n",filename.c_str());
			fptr=fopen(filename.c_str(),"r");
			for(ipar=0;ipar<NPars;ipar++){
				fscanf(fptr,"%s %lf",parname_c,&x);
				parname[ipar]=parname_c;
				theta[ipar]=-1.0+x/50.0;
				//printf("--- %s %g %g\n",parname[ipar].c_str(),x,theta[ipar]);
				if(fabs(theta[ipar])>1.0){
					printf("OOOOOUUUUUCH!!!!\n");
					exit(1);
				}
			}
			fclose(fptr);
			y=smooth.CalcY(A,LAMBDA,theta);
			filename="modelruns/run"+to_string(itrain)+"/obs.txt";
			//printf("filename_out=%s\n",filename.c_str());
			if(iobs==0)
				fptr_out=fopen(filename.c_str(),"w");
			else
				fptr_out=fopen(filename.c_str(),"a");
			fprintf(fptr_out,"%s %g 0.0\n",obsname[iobs].c_str(),y);
			fclose(fptr_out);
		}
		
		filename="fakedata/"+obsname[iobs]+".txt";
		fptr=fopen(filename.c_str(),"w");
		for(itest=0;itest<100;itest++){
			y=smooth.CalcY(A,LAMBDA,thetatest[itest]);
			for(ipar=0;ipar<NPars;ipar++){
				fprintf(fptr,"%17.10e ",thetatest[itest][ipar]);
			}
			fprintf(fptr,"%17.10e\n",y);
		}
		fclose(fptr);
	}
	
	
	
	return 0;
}
