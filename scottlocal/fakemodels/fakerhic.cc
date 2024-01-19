#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
#include "msu_commonutils/randy.h"

using namespace std;

const unsigned int NObs=6,NPars=6;

void CalcY(vector<double> &xmin,vector<double> &xmax,vector<double> &x,vector<double> &Y){
	
	vector<double> xbar,theta,t;
	xbar.resize(NPars);
	theta.resize(NPars);
	t.resize(NPars);
	for(unsigned int ipar=0;ipar<NPars;ipar++){
		xbar[ipar]=0.5*(xmin[ipar]+xmax[ipar]);
		theta[ipar]=2*(x[ipar]-xbar[ipar])/(xmax[ipar]-xmin[ipar]);
	}
	t[0]=0.5*theta[0]+0.5*theta[1]+0.5*theta[2];
	t[1]=0.5*theta[0]-0.5*theta[1]+0.5*theta[3];
	t[2]=0.1*theta[0]+0.2*theta[2]+0.3*theta[3]+0.4*theta[4]+0.5*theta[5];
	t[3]=-theta[3]-0.2*theta[5];
	t[4]=theta[4]+0.4*theta[3]-0.5*theta[6];
	t[5]=-0.5*theta[5]-0.3*theta[1]+0.1*theta[3];
	
	
	printf("t=%g,%g,%g,%g,%g,%g\n",t[0],t[1],t[2],t[3],t[4],t[5]);
	
	Y[0]=450+75*(t[0]+0.5*t[1]*t[3]+0.3*t[1]*t[1]*t[3]);
	Y[1]=725+100*(t[1]-0.5*t[2]*t[1]+0.2*t[2]*t[3]*t[4]);
	Y[2]=1100+180*(t[2]-0.5*t[3]*t[4]*t[2]);
	Y[3]=5.5+2.5*(t[3]-0.4*t[3]*t[5]+0.2*t[1]*t[2]*t[4]*t[5]);
	Y[4]=0.19+0.12*(t[4]-0.7*t[2]*t[4]);
	Y[5]=0.5-0.7*t[5];
}

int main(){
	string filename;
	char dummy[200];
	unsigned int itrain,iobs,ipar,NTrain;
	vector<double> theta,xtrue,Ytrain,Ytrue,xtrain,SigmaY;
	vector<double> xmin(NPars),xmax(NPars);
	theta.resize(NPars);
	NMSUPratt::Crandy randy(123);
	string obsname[NObs]={"meanpt_pion","meanpt_kaon","meanpt_proton","Rinv","v2","RAA"};
	string parname[NPars]={"compressibility","etaovers","initial_flow","initial_screening","quenching_length","initial_epsilon"};
	char parname_c[200],type[100];
	
	printf("Enter number of training points to read in: ");
	scanf("%d",&NTrain);
	
	FILE *fptr;
	xtrue.resize(NPars);
	Ytrue.resize(NObs);
	SigmaY.resize(NObs);
	
	xtrain.resize(NPars);
	Ytrain.resize(NObs);
	printf("NPars=%u\n",NPars);
	SigmaY[0]=15;
	SigmaY[1]=20.0;
	SigmaY[2]=30.0;
	SigmaY[3]=0.4;
	SigmaY[4]=0.02;
	SigmaY[5]=0.05;

	fptr=fopen("Info/modelpar_info.txt","r");
	fgets(dummy,200,fptr);
	for(ipar=0;ipar<NPars;ipar++){
		fscanf(fptr,"%s %s %lf %lf",parname_c,type,&xmin[ipar],&xmax[ipar]);
		xtrue[ipar]=0.4*xmin[ipar]+0.6*xmax[ipar];
	}
	fclose(fptr);
	
	CalcY(xmin,xmax,xtrue,Ytrue);
	
	fptr=fopen("Info/experimental_info.txt","w");
	for(iobs=0;iobs<NObs;iobs++){
		fprintf(fptr,"%s\t%g\t%g\n",obsname[iobs].c_str(),Ytrue[iobs],SigmaY[iobs]);
		SigmaY[iobs]=SigmaY[iobs]/10.0;
	}
	fclose(fptr);
	

	for(itrain=0;itrain<NTrain;itrain++){
		filename="modelruns/run"+to_string(itrain)+"/mod_parameters.txt";
		fptr=fopen(filename.c_str(),"r");
		for(ipar=0;ipar<NPars;ipar++){
			fscanf(fptr,"%s %lf",parname_c,&xtrain[ipar]);
		}
		fclose(fptr);
		
		CalcY(xmin,xmax,xtrain,Ytrain);
		
		filename="modelruns/run"+to_string(itrain)+"/obs.txt";
		fptr=fopen(filename.c_str(),"w");
		for(iobs=0;iobs<NObs;iobs++){
			fprintf(fptr,"%s %lf %lf\n",obsname[iobs].c_str(),Ytrain[iobs],SigmaY[iobs]);
		}
		fclose(fptr);
	}

	return 0;
}
