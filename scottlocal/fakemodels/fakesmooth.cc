#include "msu_commonutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_commonutils/log.h"

using namespace std;
int main(int argc,char *argv[]){

	const int NObs=3,NPars=20,NTrain=43;
	int itrain,iobs,ic,ipar,maxrank=5;
	double LAMBDA=2.5;
	double y,x;
	vector<double> A;
	vector<double> theta;
	theta.resize(NPars);
	NMSUPratt::Crandy randy(0);
	
	NBandSmooth::CSmooth smooth(NPars,maxrank);
	A.resize(smooth.NCoefficients);
	
	string obsname[NObs]={"mass","length","time"};
	string parname[NPars];
	char parname_c[200];
	string filename;
	FILE *fptr,*fptr_out;
	for(iobs=0;iobs<NObs;iobs++){
		randy.reset(iobs);
		for(itrain=0;itrain<NTrain;itrain++){
			filename="modelruns/run"+to_string(itrain)+"/mod_parameters.txt";
			printf("filename=%s\n",filename.c_str());
			fptr=fopen(filename.c_str(),"r");
			for(ipar=0;ipar<NPars;ipar++){
				fscanf(fptr,"%s %lf",parname_c,&x);
				parname[ipar]=parname_c;
				theta[ipar]=-1.0+x/50.0;
				printf("--- %s %g %g\n",parname[ipar].c_str(),x,theta[ipar]);
				if(fabs(theta[ipar])>1.0){
					printf("OOOOOUUUUUCH!!!!\n");
					exit(1);
				}
			}
			fclose(fptr);
			for(ic=0;ic<smooth.NCoefficients;ic++){
				A[ic]=100.0*randy.ran_gauss();
			}
			printf("check\n");
			y=smooth.CalcY(A,LAMBDA,theta);

			filename="modelruns/run"+to_string(itrain)+"/obs.txt";
			printf("filename_out=%s\n",filename.c_str());
			if(iobs==0)
				fptr_out=fopen(filename.c_str(),"w");
			else
				fptr_out=fopen(filename.c_str(),"a");
			fprintf(fptr_out,"%s %g 0.0\n",obsname[iobs].c_str(),y);
			fclose(fptr_out);
		}
	}
	return 0;
}
