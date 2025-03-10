#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/smooth.h"
#include "msu_smoothutils/log.h"
#include "msu_smoothutils/parametermap.h"
#include <filesystem>

using namespace std;
using namespace NMSUUtils;
int main(){
	bool gu=false;
	double GSCALE=sqrt(3.0);
	double ALPHA,thetascale;
	char dummy[400];
	unsigned int NObs,NPars;
	unsigned int NTrain,itrain,ic,ipar,maxrank=5,iy;
	double LAMBDA;
	CparameterMap parmap;
	vector<vector<double>> A;
	vector<vector<double>> xtrain, thetatrain;
	vector<double> theta,exptheta,SigmaY,Ytrain;
	vector<string> priortype;
	string expfilename,filename,command;
	vector<string> obsname;
	vector<string> parname;
	vector<double> xmin,xmax,x0,Rgauss,thetatrue,ytrue;
	char parname_c[200],type[100],typeread[10];
	FILE *fptr;
	NMSUUtils::Crandy randy(-time(NULL));
	//NMSUUtils::Crandy randy(-123);

	parmap.ReadParsFromFile("smooth_data/smooth_parameters/simplex_parameters.txt");
	parmap.ReadParsFromFile("smooth_data/smooth_parameters/emulator_parameters.txt");
	fptr=fopen("NParsNObs.txt","r");
	fgets(dummy,400,fptr);
	fscanf(fptr,"%d %d %lf %lf",&NPars,&NObs,&ALPHA,&thetascale);
	fclose(fptr);
	printf("NPars=%d, NObs=%d, ALPHA=%g, thetascale=%g\n",NPars,NObs,ALPHA,thetascale);
	
	printf("Enter Lambda for fakesmooth: ");
	scanf("%lf",&LAMBDA);
	printf("Enter u or g for gaussian/uniform prior: ");
	scanf("%s",typeread);
	if(typeread[0]=='u')
		gu=false;
	else if(typeread[0]=='g')
		gu=true;
	else
		CLog::Fatal("must enter g or u\n");

	thetatrue.resize(NPars);
	ytrue.resize(NObs);
	SigmaY.resize(NObs);
	xmin.resize(NPars);
	xmax.resize(NPars);
	x0.resize(NPars);
	Rgauss.resize(NPars);
	obsname.resize(NObs);
	Ytrain.resize(NObs);

	// Find NTrain
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
	xtrain.resize(NTrain);
	thetatrain.resize(NTrain);
	for(itrain=0;itrain<NTrain;itrain++){
		xtrain[itrain].resize(NPars);
		thetatrain[itrain].resize(NPars);
	}
	CLog::Info("NTraining Pts="+to_string(NTrain)+"\n");

	// Create smooth object
	NBandSmooth::CSmooth smooth(NPars,maxrank);


	// Create A for smooth object
	A.resize(NObs);
	for(iy=0;iy<NObs;iy++){
		A[iy].resize(smooth.NCoefficients);
		for(ic=0;ic<smooth.NCoefficients;ic++){
			A[iy][ic]=100.0*randy.ran_gauss();
		}
	}
	
	// Observable uncertainties
	for(iy=0;iy<NObs;iy++){
		SigmaY[iy]=5.0;
		obsname[iy]="obs"+to_string(iy);
	}
	
	// read in modelpar_info and set experimental value to theta=0.2
	fptr=fopen("smooth_data/Info/modelpar_info.txt","r");
	fgets(dummy,400,fptr);
	for(ipar=0;ipar<NPars;ipar++){
		fscanf(fptr,"%s %s %lf %lf %lf",parname_c,type,&xmin[ipar],&xmax[ipar],&thetascale);
		if(gu){
			x0[ipar]=xmin[ipar];
			Rgauss[ipar]=xmax[ipar];
		}
		parname.push_back(string(parname_c));
		thetatrue[ipar]=0.2;
	}
	fclose(fptr);
	fptr=fopen("smooth_data/Info/experimental_info.txt","w");
	for(iy=0;iy<NObs;iy++){
		ytrue[iy]=smooth.CalcY(A[iy],LAMBDA,thetatrue);
		fprintf(fptr,"%s\t%g\t%g 0.0\n",
		obsname[iy].c_str(),ytrue[iy],SigmaY[iy]);
	}
	fclose(fptr);
	
	// write observables at training pts
	FILE *fptr_thetas=fopen("SigmaVsLambda/TrainingThetas.txt","w");
	FILE *fptr_obs=fopen("SigmaVsLambda/TrainingObs.txt","w");
	FILE *fptr_SigmaY=fopen("SigmaVsLambda/TrainingSigmaY.txt","w");
	
	for(itrain=0;itrain<NTrain;itrain++){
		filename="smooth_data/modelruns/run"+to_string(itrain)+"/mod_parameters.txt";
		fptr=fopen(filename.c_str(),"r");
		for(ipar=0;ipar<NPars;ipar++){
			fscanf(fptr,"%s %lf",parname_c,&xtrain[itrain][ipar]);
			fprintf(fptr_thetas,"%15.8f ",xtrain[itrain][ipar]);
			if(gu){
				thetatrain[itrain][ipar]=(xtrain[itrain][ipar]-x0[ipar])/(Rgauss[ipar]*GSCALE);
			}
			else{
				thetatrain[itrain][ipar]=-1.0+2.0*(xtrain[itrain][ipar]-xmin[ipar])/(xmax[ipar]-xmin[ipar]);
			}
		}
		fprintf(fptr_thetas,"\n");
		fclose(fptr);	

		filename="smooth_data/modelruns/run"+to_string(itrain)+"/obs.txt";
		fptr=fopen(filename.c_str(),"w");
		for(iy=0;iy<NObs;iy++){
			Ytrain[iy]=smooth.CalcY(A[iy],LAMBDA,thetatrain[itrain]);

			double randomerror=0.0;
			fprintf(fptr,"%s %lf %lf\n",obsname[iy].c_str(),Ytrain[iy],randomerror);
			fprintf(fptr_obs,"%15.8f ",Ytrain[iy]);
			fprintf(fptr_SigmaY,"%15.8f ",SigmaY[iy]);
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
	vector<vector<double>> thetatest,xtest;
	int itest,Ntest=1000;
	double y;
	
	thetatest.resize(Ntest);
	xtest.resize(Ntest);
	for(itest=0;itest<Ntest;itest++){
		thetatest[itest].resize(NPars);
		xtest[itest].resize(NPars);
		for(ipar=0;ipar<NPars;ipar++){
			if(gu){
				thetatest[itest][ipar]=-1.0+2.0*randy.ran();
			}
			else{
				thetatest[itest][ipar]=randy.ran_gauss()/GSCALE;
			}
			if(gu){
				xtest[itest][ipar]=x0[ipar]+Rgauss[ipar]*thetatest[itest][ipar]*GSCALE;
			}
			else{
				xtest[itest][ipar]=xmin[ipar]
				+0.5*(1.0+thetatest[itest][ipar])*(xmax[ipar]-xmin[ipar]);
			}

		}
	}
	
	command="mkdir -p smooth_data/fullmodel_testdata";
	system(command.c_str());
	for(iy=0;iy<NObs;iy++){
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
		
	}

	// write experimental data (for use with mcmc)
	FILE *expfptr;
	expfilename="smooth_data/Info/experimental_info.txt";
	expfptr=fopen(expfilename.c_str(),"w");
	exptheta.resize(NPars);
	for(ipar=0;ipar<NPars;ipar++){
		exptheta[ipar]=0.2;
	}
	for(iy=0;iy<NObs;iy++){
		y=smooth.CalcY(A[iy],LAMBDA,exptheta);
		fprintf(expfptr,"%s  %lf  3.0 0.0\n",obsname[iy].c_str(),y);
	}
	
	fclose(expfptr);
	
	
	return 0;
}
