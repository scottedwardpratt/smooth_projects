#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/smooth.h"
#include "msu_smoothutils/log.h"
#include "msu_smoothutils/parametermap.h"
#include <filesystem>

using namespace std;
using namespace NMSUUtils;
int main(){

	unsigned int NObs,NPars;
	unsigned int NTrain,itrain,ic,ipar,maxrank=4,iobs;
	double LAMBDA,y;
	CparameterMap parmap;
	vector<vector<double>> A;
	vector<double> theta,exptheta,X,SigmaY,xtrain,Ytrain;
	vector<string> priortype;
	char dummy[400];
	string expfilename,filename,command;
	vector<string> obsname;
	vector<string> parname;
	vector<double> xmin,xmax,thetatrue,ytrue;
	FILE *fptr;
	NMSUUtils::Crandy randy(-time(NULL));
	char parname_c[200],type[100];
	parmap.ReadParsFromFile("smooth_data/smooth_parameters/simplex_parameters.txt");
	parmap.ReadParsFromFile("smooth_data/smooth_parameters/emulator_parameters.txt");
	fptr=fopen("NParsNObs.txt","r");
	fscanf(fptr,"%d %d",&NPars,&NObs);
	fclose(fptr);
	
	printf("Enter LAMBDA for fakesmooth: ");
	scanf("%lf",&LAMBDA);
	
	NTrain=0;
	bool existence;
	do{
		string filename="smooth_data/modelruns/run"+to_string(NTrain);
		filesystem::path f{filename};
		existence=filesystem::exists(f);
		if(existence){
			NTrain+=1;
		}
	}while(existence);
	CLog::Info("NTraining Pts="+to_string(NTrain)+"\n");
	NBandSmooth::CSmooth smooth(NPars,maxrank);
	
	thetatrue.resize(NPars);
	theta.resize(NPars);
	ytrue.resize(NObs);
	SigmaY.resize(NObs);
	xmin.resize(NPars);
	xmax.resize(NPars);
	X.resize(NPars);
	obsname.resize(NObs);
	
	xtrain.resize(NPars);
	Ytrain.resize(NObs);
	
	A.resize(NObs);
	for(iobs=0;iobs<NObs;iobs++){
		A[iobs].resize(smooth.NCoefficients);
		for(ic=0;ic<smooth.NCoefficients;ic++){
			A[iobs][ic]=100.0*randy.ran_gauss();
		}
	}
	
	// Observable uncertainties
	for(iobs=0;iobs<NObs;iobs++){
		SigmaY[iobs]=5.0;
		obsname[iobs]="obs"+to_string(iobs);
	}
	
	// read in modelpar_info and set experimental value to theta=0.2
	fptr=fopen("smooth_data/Info/modelpar_info.txt","r");
	fgets(dummy,200,fptr);
	for(ipar=0;ipar<NPars;ipar++){
		fscanf(fptr,"%s %s %lf %lf",parname_c,type,&xmin[ipar],&xmax[ipar]);
		parname.push_back(string(parname_c));
		thetatrue[ipar]=0.2;
	}
	fclose(fptr);
	fptr=fopen("smooth_data/Info/experimental_info.txt","w");
	for(iobs=0;iobs<NObs;iobs++){
		ytrue[iobs]=smooth.CalcY(A[iobs],LAMBDA,thetatrue);
		fprintf(fptr,"%s\t%g\t%g 0.0\n",
		obsname[iobs].c_str(),ytrue[iobs],SigmaY[iobs]);
	}
	fclose(fptr);
	
	// write output at training pts
	
	FILE *fptr_thetas=fopen("SigmaVsLambda/TrainingThetas.txt","w");
	FILE *fptr_obs=fopen("SigmaVsLambda/TrainingObs.txt","w");
	FILE *fptr_SigmaY=fopen("SigmaVsLambda/TrainingSigmaY.txt","w");
	
	for(itrain=0;itrain<NTrain;itrain++){
		filename="smooth_data/modelruns/run"+to_string(itrain)+"/mod_parameters.txt";
		fptr=fopen(filename.c_str(),"r");
		for(ipar=0;ipar<NPars;ipar++){
			fscanf(fptr,"%s %lf",parname_c,&xtrain[ipar]);
			fprintf(fptr_thetas,"%15.8f ",xtrain[ipar]);
			theta[ipar]=-1.0+2.0*(xtrain[ipar]-xmin[ipar])/(xmax[ipar]-xmin[ipar]);
		}
		fprintf(fptr_thetas,"\n");
		fclose(fptr);		
		
		filename="smooth_data/modelruns/run"+to_string(itrain)+"/obs.txt";
		fptr=fopen(filename.c_str(),"w");
		
		for(iobs=0;iobs<NObs;iobs++){
			y=smooth.CalcY(A[iobs],LAMBDA,theta);

			double randomerror=0.0*y;
			fprintf(fptr,"%s %lf %lf\n",obsname[iobs].c_str(),y,randomerror);
			fprintf(fptr_obs,"%15.8f ",y);
			fprintf(fptr_SigmaY,"%15.8f ",SigmaY[iobs]);
		}
		fclose(fptr);
		fprintf(fptr_obs,"\n");
		fprintf(fptr_SigmaY,"\n");
		
		
	}
	fclose(fptr_thetas);
	fclose(fptr_obs);
	fclose(fptr_SigmaY);
	
	//
	
	// Now make some data for later testing, not for tuning
	FILE *expfptr;
	int iy,it=time(NULL);
	double x;
	vector<vector<double>> thetatest;
	int itest,Ntest=50;
	FILE *fptr_out;
	
	thetatest.resize(Ntest);
	for(itest=0;itest<Ntest;itest++){
		thetatest[itest].resize(NPars);
		for(ipar=0;ipar<NPars;ipar++){
			thetatest[itest][ipar]=-1.0+2.0*randy.ran();
		}
	}
	
	command="mkdir -p smooth_data/fullmodel_testdata";
	system(command.c_str());
	theta.resize(NPars);
	A.resize(NObs);
	expfilename="smooth_data/Info/experimental_info.txt";
	expfptr=fopen(expfilename.c_str(),"w");
	exptheta.resize(NPars);
	for(ipar=0;ipar<NPars;ipar++){
		exptheta[ipar]=0.2;
	}
	
	for(iy=0;iy<int(NObs);iy++){
		A[iy].resize(NPars);
		randy.reset(iy+it);
		for(ic=0;ic<smooth.NCoefficients;ic++){
			A[iy][ic]=100.0*randy.ran_gauss();
		}
		for(itrain=0;itrain<NTrain;itrain++){
			filename="smooth_data/modelruns/run"+to_string(itrain)+"/mod_parameters.txt";
			fptr=fopen(filename.c_str(),"r");
			for(ipar=0;ipar<NPars;ipar++){
				fscanf(fptr,"%s %lf",parname_c,&x);
				parname[ipar]=parname_c;
				theta[ipar]=-1.0+2.0*(x-xmin[ipar])/(xmax[ipar]-xmin[ipar]);
			}
			fclose(fptr);
			
			y=smooth.CalcY(A[iy],LAMBDA,theta);
			filename="smooth_data/modelruns/run"+to_string(itrain)+"/obs.txt";
			if(iy==0)
				fptr_out=fopen(filename.c_str(),"w");
			else
				fptr_out=fopen(filename.c_str(),"a");
			fprintf(fptr_out,"%s %g\n",obsname[iy].c_str(),y);
			fclose(fptr_out);
		}

		filename="smooth_data/fullmodel_testdata/"+obsname[iy]+".txt";
		fptr=fopen(filename.c_str(),"w");
		for(itest=0;itest<Ntest;itest++){
			y=smooth.CalcY(A[iy],LAMBDA,thetatest[itest]);
			for(ipar=0;ipar<NPars;ipar++){
				fprintf(fptr,"%17.10e ",thetatest[itest][ipar]);
			}
			fprintf(fptr,"%17.10e\n",y);
		}
		fclose(fptr);
		
		y=smooth.CalcY(A[iy],LAMBDA,exptheta);
		fprintf(expfptr,"%s  %lf  3.0 0.0\n",obsname[iy].c_str(),y);
	}
	
	fclose(expfptr);
	
	
	
	return 0;
}
