#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
#include "msu_commonutils/randy.h"

void const int NObs=6,NPars=6;
void CalcY(vector<double> &xmin,vector<double> &xmax,vector<double> &xtrue,vector<double> &x,vector<double> &Y){
	
}

using namespace std;
int main(int argc,char *argv[]){
	string filename;
	int itrain,iobs,ipar,i,NTrain;
	vector<double> theta,xtrue,Ytrain,Ytrue,xtrue,xmin,xmax,xtrain;
	theta.resize(NPars);
	NMSUPratt::Crandy randy(123);
	string obsname[NObs]={"meanpt_pion","meanpt_kaon","meanpt_proton","Rinv","v2","RAA"};
	string parname[NPars]={"compressibility","etaovers","initial_flow","initial_screening","quenching_length","initial_epsilon"};
	char parname_c[200],type[100];
	
	printf("Enter number of training points to read in: ");
	scanf("%d",&NTrain);
	
	FILE *fptr,*fptr_out;
	xtrue.resize(NPars);
	Ytrue.resize(NPars);
	xtrain.resize(NPars);
	Ytrain.resize(NPars);
	xmin.resize(NPars);
	xmax.resize(NPars);
	xmin={150.0,0.05,0.3,0.0,0.5,15.0};
	xmax={300,0.32,1.2,1.0,2.0,30.0};
	fptr=fopen("Info/modelpar_info.txt","r");
	for(ipar=0;ipar<NPars;ipar++){
		fscanf(fptr,"%s %s %lf %lf",parname_c,type,&xmin[ipar],&xmax[ipar]);
		xtrue[ipar]=0.6*xmin[ipar]+0.4*xmax[ipar];
	}
	fclose(fptr);
	
	CalcY(xmin,xmax,xtrue,xtrue,Ytrue);
	

	for(itrain=0;itrain<NTrain;itrain++){
		filename="modelruns/run"+to_string(itrain)+"/mod_parameters.txt";
		printf("filename=%s\n",filename.c_str());
		fptr=fopen(filename.c_str(),"r");
		for(ipar=0;ipar<NPars;ipar++){
			fscanf(fptr,"%s %lf",parname_c,&xtrain[ipar]);
		}
		fclose(fptr);
		
		CalcY(xmin,xmax,xtrue,xtrain,Ytrain);
		
		filename="modelruns/run"+to_string(itrain)+"/obs.txt";
		printf("filename_out=%s\n",filename.c_str());
		fptr_out=fopen(filename.c_str(),"w");
		for(iy=0;iy<NObs;iy++){
			fprintf(fptr,"%s %lf",obsname[iy],Y[ipar]);
		}
		fclose(fptr);
	}

	return 0;
}
