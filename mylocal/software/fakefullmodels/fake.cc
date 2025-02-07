#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
#include <filesystem>
#include "msu_smoothutils/randy.h"
#include "msu_smoothutils/log.h"

using namespace std;
using namespace NMSUUtils;
const unsigned int NObs=10,NPars=6;
double GSCALE=sqrt(3.0);

void CalcY(vector<double> &X0,vector<double> &RGauss,vector<double> &x,vector<double> &Y,Crandy *randy,double Lambda){
	unsigned int iy,ipar,NObs=Y.size();
	vector<double> theta,t,D,alpha;
	theta.resize(NPars);
	D.resize(NPars);
	t.resize(NPars);
	alpha.resize(NPars);
	for(ipar=0;ipar<NPars;ipar++){
		theta[ipar]=(x[ipar]-X0[ipar])/(GSCALE*RGauss[ipar]);
	}
	
	t[0]=0.5*theta[0]+0.5*theta[1]+0.5*theta[2]+0.5*theta[3]+0.5*theta[4]+0.5*theta[5];
	t[1]=theta[1]-theta[2]+theta[0]*theta[1]/Lambda+theta[1]*theta[2]/Lambda;
	t[2]=theta[2]-theta[3]+theta[1]*theta[2]/Lambda+theta[2]*theta[3]/Lambda;
	t[3]=theta[3]-theta[4]+theta[2]*theta[3]/Lambda+theta[3]*theta[2]/Lambda;
	t[4]=theta[4]-theta[5]+theta[3]*theta[4]/Lambda+theta[4]*theta[5]/Lambda;	
	t[5]=0.5*theta[0]-0.5*theta[1]+0.5*theta[2]-0.5*theta[3]+0.5*theta[4]-0.5*theta[5];
	
	for(iy=0;iy<NObs;iy++){
		randy->reset(iy);
		Y[iy]=100.0*randy->ran();
		for(ipar=0;ipar<NPars;ipar++){
			D[ipar]=100.0*randy->ran();
		}
		for(ipar=0;ipar<NPars;ipar++){
			alpha[ipar]=randy->ran_gauss()/Lambda;
			Y[iy]+=D[0]*cos(alpha[0]*t[0])+D[1]*sin(alpha[1]*t[1])+D[2]*atan(alpha[2]*t[2])
			+D[3]*cosh(alpha[3]*t[3])+D[4]*sinh(alpha[4]*t[4])+D[5]*tanh(alpha[5]*t[5]);
		}
	}
}

int main(){
	string filename;
	FILE *fptr;
	char dummy[200];
	unsigned int itrain,iobs,ipar,NTrain;
	vector<double> theta,xtrue,Ytrain,Ytrue,SigmaY,Y,X;
	vector<vector<double>> xtrain;
	vector<double> X0(NPars),RGauss(NPars);
	theta.resize(NPars);
	NMSUUtils::Crandy randy(123);
	string obsname[NObs]={"obs0","obs1","obs2","obs3","obs4","obs5","obs6","obs7","obs8","obs9",};
	string parname[NPars]={"par0","par1","par2","par3","par4","par5"};
	char parname_c[200],type[100];
	double Lambda;
	bool existence;
	printf("Enter Lambda: ");
	scanf("%lf",&Lambda);
	
	NTrain=0;
	do{
		string filename="smooth_data/modelruns/run"+to_string(NTrain);
		filesystem::path f{filename};
		existence=filesystem::exists(f);
		if(existence){
			NTrain+=1;
		}
	}while(existence);
	CLog::Info("NTraining Pts="+to_string(NTrain)+"\n");
	CLog::Info("NPars="+to_string(NPars)+"\n");
	xtrue.resize(NPars);
	Ytrue.resize(NObs);
	Y.resize(NObs);
	SigmaY.resize(NObs);
	
	xtrain.resize(NTrain);
	for(itrain=0;itrain<NTrain;itrain++){
		xtrain[itrain].resize(NPars);
		for(ipar=0;ipar<NPars;ipar++){
			xtrain[itrain][ipar]=0.0;
		}
	}
	Ytrain.resize(NObs);

	// Observable uncertainties
	SigmaY[0]=0.0;
	SigmaY[1]=0.0;
	SigmaY[2]=0.0;
	SigmaY[3]=0.0;
	SigmaY[4]=0.0;
	SigmaY[5]=0.0;

	// read in modelpar_info and set experimental value to theta=0.2
	fptr=fopen("smooth_data/Info/modelpar_info.txt","r");
	fgets(dummy,200,fptr);
	for(ipar=0;ipar<NPars;ipar++){
		fscanf(fptr,"%s %s %lf %lf",parname_c,type,&X0[ipar],&RGauss[ipar]);
		xtrue[ipar]=X0[ipar]+0.6*RGauss[ipar];
	}
	fclose(fptr);
	CalcY(X0,RGauss,xtrue,Ytrue,&randy,Lambda);
	fptr=fopen("smooth_data/Info/experimental_info.txt","w");
	for(iobs=0;iobs<NObs;iobs++){
		fprintf(fptr,"%s\t%g\t%g 0.0\n",
		obsname[iobs].c_str(),Ytrue[iobs],SigmaY[iobs]);
	}
	fclose(fptr);
	
	// Write observable info for every training point
	
	FILE *fptr_thetas=fopen("SigmaVsLambda/TrainingThetas.txt","w");
	FILE *fptr_obs=fopen("SigmaVsLambda/TrainingObs.txt","w");
	FILE *fptr_sigmay=fopen("SigmaVsLambda/TrainingSigmaY.txt","w");
	
	for(itrain=0;itrain<NTrain;itrain++){
		filename="smooth_data/modelruns/run"+to_string(itrain)+"/mod_parameters.txt";
		fptr=fopen(filename.c_str(),"r");
		for(ipar=0;ipar<NPars;ipar++){
			fscanf(fptr,"%s %lf",parname_c,&xtrain[itrain][ipar]);
			fprintf(fptr_thetas,"%15.8f ",xtrain[itrain][ipar]);
		}
		fprintf(fptr_thetas,"\n");
		fclose(fptr);
		
		CalcY(X0,RGauss,xtrain[itrain],Ytrain,&randy,Lambda);
		
		filename="smooth_data/modelruns/run"+to_string(itrain)+"/obs.txt";
		fptr=fopen(filename.c_str(),"w");
		for(iobs=0;iobs<NObs;iobs++){
			double randomerror=0.0*Ytrain[iobs];
			fprintf(fptr,"%s %lf %lf\n",obsname[iobs].c_str(),Ytrain[iobs],randomerror);
			fprintf(fptr_obs,"%15.8f ",Ytrain[iobs]);
			fprintf(fptr_sigmay,"%15.8f ",SigmaY[iobs]);
		}
		fclose(fptr);
		fprintf(fptr_obs,"\n");
		fprintf(fptr_sigmay,"\n");
		
	}
	fclose(fptr_thetas);
	fclose(fptr_obs);
	fclose(fptr_sigmay);
	
	// Write fullmodel test data for random points
	X.resize(NPars);
	string command="mkdir -p smooth_data/fullmodel_testdata";
	system(command.c_str());
	command="rm -f smooth_data/fullmodel_testdata/*.txt";
	system(command.c_str());
	unsigned int itest,Ntest=50;

	for(iobs=0;iobs<NObs;iobs++){
		filename="smooth_data/fullmodel_testdata/"+obsname[iobs]+".txt";
		fptr=fopen(filename.c_str(),"w");
		for(itest=0;itest<Ntest;itest++){
			randy.reset(iobs*100000+itest);
			for(ipar=0;ipar<NPars;ipar++){
				X[ipar]=X0[ipar]+RGauss[ipar]*randy.ran_gauss();
				theta[ipar]=(X[ipar]-X0[ipar])/(GSCALE*RGauss[ipar]);
			}
			CalcY(X0,RGauss,X,Y,&randy,Lambda);
			for(ipar=0;ipar<NPars;ipar++){
				fprintf(fptr,"%12.5e ",theta[ipar]);
			}
			fprintf(fptr,"%12.5e\n",Y[iobs]);
		}
		fclose(fptr);
	}
	return 0;
}
