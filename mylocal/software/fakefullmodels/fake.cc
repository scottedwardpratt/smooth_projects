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
unsigned int NObs,NPars,IFAKE=2;
double GSCALE=sqrt(3.0);

void CalcY(vector<double> &X0,vector<double> &RGauss,vector<double> &x,vector<double> &Y,Crandy *randy){
	unsigned int iy,ipar,jpar,iterm,NObs=Y.size();
	unsigned int nterms=6;
	vector<double> theta,t,D;
	vector<double> Lambda;
	double lambda;
	theta.resize(NPars);
	D.resize(nterms);
	t.resize(nterms);
	Lambda.resize(nterms);
	//printf("GSCALE=%g, RGauss=(%g,%g,%g,%g,%g,%g)\n",GSCALE,RGauss[0],RGauss[1],RGauss[2],RGauss[3],RGauss[4],RGauss[5]);
	for(ipar=0;ipar<NPars;ipar++){
		theta[ipar]=(x[ipar]-X0[ipar])/(GSCALE*RGauss[ipar]);
	}
	//printf("theta=(%g,%g,%g,%g,%g,%g)\n",theta[0],theta[1],theta[2],theta[3],theta[4],theta[5]);

	for(iy=0;iy<NObs;iy++){
		randy->reset(100*IFAKE+iy);
		for(iterm=0;iterm<nterms;iterm++){
			t[iterm]=0.0;
			for(ipar=0;ipar<NPars;ipar++){
				t[iterm]+=(1.0-2.0*randy->ran())*theta[ipar]/sqrt(nterms);
				for(jpar=0;jpar<NPars;jpar++){
					lambda=2.0+5.0*randy->ran();
					t[iterm]+=(1.0-2.0*randy->ran())*theta[ipar]*theta[jpar]/lambda;
				}
			}
		}

		Y[iy]=0.0;//100.0*randy->ran();
		for(iterm=0;iterm<nterms;iterm++){
			D[iterm]=100.0*(1.0-2.0*randy->ran());
			Lambda[iterm]=2.0+5.0*randy->ran();
		}
		double t5=t[5]/Lambda[5];
		t5=t5/sqrt(1.0+t5*t5);
		Y[iy]=D[0]*cos(t[0]/Lambda[0])
			+D[1]*sin(t[1]/Lambda[1])
				+D[2]*atan(t[2]/Lambda[2])
					+D[3]*cosh(t[3]/Lambda[3])
						+D[4]*sinh(t[4]/Lambda[4])
							+D[5]*atanh(t5);
		if(Y[iy]!=Y[iy]){
			for(iterm=0;iterm<6;iterm++){
				printf("iy=%u, D=%g, t=%g, Lambda=%g, Y=%g\n",iy,D[iterm],t[iterm],Lambda[iterm],Y[iy]);
			}
			CLog::Fatal("iy="+to_string(iy)+": Y!=Y\n");
		}
	}
}

int main(){
	string filename;
	FILE *fptr;
	char dummy[300];
	unsigned int itrain,iobs,ipar,NTrain;
	double ALPHA=0.01,ThetaScale;
	vector<double> theta,xtrue,Ytrain,Ytrue,SigmaY,Y,X;
	vector<vector<double>> xtrain;
	vector<double> X0,RGauss;
	NMSUUtils::Crandy randy(123);
	vector<string> obsname;//={"obs0","obs1","obs2","obs3","obs4","obs5","obs6","obs7","obs8","obs9",};
	vector<string> parname;//={"par0","par1","par2","par3","par4","par5"};
	char parname_c[200],type[100];
	bool existence;
	
	fptr=fopen("NParsNObs.txt","r");
	fgets(dummy,300,fptr);
	fscanf(fptr,"%u %u %lf %lf",&NPars,&NObs,&ALPHA,&ThetaScale);
	fclose(fptr);
	CLog::Info("NPars="+to_string(NPars)+", NObs="+to_string(NObs)+"\n");
	X0.resize(NPars);
	RGauss.resize(NPars);
	obsname.resize(NObs);
	parname.resize(NPars);
	theta.resize(NPars);
	xtrue.resize(NPars);
	Ytrue.resize(NObs);
	Y.resize(NObs);
	SigmaY.resize(NObs);
	Ytrain.resize(NObs);
	
	for(iobs=0;iobs<NObs;iobs++)
		obsname[iobs]="obs"+to_string(iobs);
	for(ipar=0;ipar<NPars;ipar++)
		parname[ipar]="par"+to_string(ipar);
	
	
	NTrain=0;
	do{
		string filename="smooth_data/FullModelRuns/run"+to_string(NTrain);
		filesystem::path f{filename};
		existence=filesystem::exists(f);
		if(existence){
			NTrain+=1;
		}
	}while(existence);
	CLog::Info("NTraining Pts="+to_string(NTrain)+"\n");
	
	xtrain.resize(NTrain);
	for(itrain=0;itrain<NTrain;itrain++){
		xtrain[itrain].resize(NPars);
		for(ipar=0;ipar<NPars;ipar++){
			xtrain[itrain][ipar]=0.0;
		}
	}
	
	// Observable uncertainties
	SigmaY[0]=0.0;
	SigmaY[1]=0.0;
	SigmaY[2]=0.0;
	SigmaY[3]=0.0;
	SigmaY[4]=0.0;
	SigmaY[5]=0.0;

	// read in modelpar_info and set experimental value to theta=0.2
	fptr=fopen("smooth_data/Info/modelpar_info.txt","r");
	fgets(dummy,300,fptr);
	for(ipar=0;ipar<NPars;ipar++){
		fscanf(fptr,"%s %s %lf %lf %lf",parname_c,type,&X0[ipar],&RGauss[ipar],&ThetaScale);
		xtrue[ipar]=X0[ipar]+0.6*RGauss[ipar];
	}
	fclose(fptr);
	CalcY(X0,RGauss,xtrue,Ytrue,&randy);
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
		filename="smooth_data/FullModelRuns/run"+to_string(itrain)+"/model_parameters.txt";
		fptr=fopen(filename.c_str(),"r");
		for(ipar=0;ipar<NPars;ipar++){
			fscanf(fptr,"%s %lf",parname_c,&xtrain[itrain][ipar]);
			fprintf(fptr_thetas,"%15.8f ",xtrain[itrain][ipar]);
		}
		fprintf(fptr_thetas,"\n");
		fclose(fptr);
		
		CalcY(X0,RGauss,xtrain[itrain],Ytrain,&randy);
		/*
		printf("---- itrain=%u -----\n",itrain);
		for(ipar=0;ipar<NPars;ipar++)
		printf("%8.4f ",xtrain[itrain][ipar]);
		printf("\n");
		*/
		
		filename="smooth_data/FullModelRuns/run"+to_string(itrain)+"/obs.txt";
		fptr=fopen(filename.c_str(),"w");
		for(iobs=0;iobs<NObs;iobs++){
			fprintf(fptr,"%s %lf %lf\n",obsname[iobs].c_str(),Ytrain[iobs],ALPHA);
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
	for(iobs=0;iobs<NObs;iobs++){
		command="rm -f smooth_data/fullmodel_testdata/obs"+to_string(iobs)+".txt";
		system(command.c_str());
	}
	unsigned int itest,Ntest=1000;

	for(itest=0;itest<Ntest;itest++){
		printf("---- itest=%u -----\n",itest);
		randy.reset(itest);
		for(ipar=0;ipar<NPars;ipar++){
			X[ipar]=X0[ipar]+RGauss[ipar]*randy.ran_gauss();
			theta[ipar]=(X[ipar]-X0[ipar])/(GSCALE*RGauss[ipar]);
		}
		CalcY(X0,RGauss,X,Y,&randy);
		for(iobs=0;iobs<NObs;iobs++){
			filename="smooth_data/fullmodel_testdata/"+obsname[iobs]+".txt";
			fptr=fopen(filename.c_str(),"a");
			for(ipar=0;ipar<NPars;ipar++){
				fprintf(fptr,"%12.5e ",theta[ipar]);
			}
			fprintf(fptr,"%12.5e\n",Y[iobs]);
			fclose(fptr);
		}
	}

	return 0;
}
