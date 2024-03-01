#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_smooth/PCA.h"

using namespace std;

int main() {
	CparameterMap parmap;
	parmap.ReadParsFromFile("parameters/emulator_parameters.txt");
  NBandSmooth::PCA *pca = new NBandSmooth::PCA(&parmap);

  pca->ReadTransformationInfo();
	
	vector<double> Z,Y,SigmaZ_emulator,SigmaY_emulator;
	
	Z.resize(pca->Nobs);
	Y.resize(pca->Nobs);
	SigmaZ_emulator.resize(pca->Nobs);
	SigmaY_emulator.resize(pca->Nobs);
	
	printf("---- Start with these values of Z ----\n");
	for(unsigned int iobs=0;iobs<pca->Nobs;iobs++){
		Z[iobs]=iobs;
		printf("Z[%u]=%g\n",iobs,Z[iobs]);
	}
	
	printf("---- Translated values of Y ----\n");
	SigmaZ_emulator[0]=SigmaZ_emulator[1]=SigmaZ_emulator[2]=SigmaZ_emulator[3]=SigmaZ_emulator[4]=SigmaZ_emulator[5]=1.0;
		
	pca->TransformZtoY(Z,SigmaZ_emulator,Y,SigmaY_emulator);
	for(unsigned int iobs=0;iobs<pca->Nobs;iobs++){
		printf("%10.5f %10.5f\n",Y[iobs],SigmaY_emulator[iobs]);
	}
	
	printf("---- (Re)Translated values of Z ----\n");
	pca->TransformYtoZ(Y,SigmaY_emulator,Z,SigmaZ_emulator);
	for(unsigned int iobs=0;iobs<pca->Nobs;iobs++){
		printf("%10.5f %10.5f\n",Z[iobs],SigmaZ_emulator[iobs]);
	}
	printf("---- Retranslated values of Z should match original and SigmaZ should all be unity ----\n");
	
	printf("---- Translated values of Y ----\n");
	SigmaZ_emulator[0]=SigmaZ_emulator[1]=SigmaZ_emulator[2]=SigmaZ_emulator[3]=SigmaZ_emulator[4]=SigmaZ_emulator[5]=1.0;
		
	pca->TransformZtoY(Z,SigmaZ_emulator,Y,SigmaY_emulator);
	for(unsigned int iobs=0;iobs<pca->Nobs;iobs++){
		printf("%10.5f %10.5f\n",Y[iobs],SigmaY_emulator[iobs]);
	}
	
	printf("---- (Re)Translated values of Z ----\n");
	pca->TransformYtoZ(Y,SigmaY_emulator,Z,SigmaZ_emulator);
	for(unsigned int iobs=0;iobs<pca->Nobs;iobs++){
		printf("%10.5f %10.5f\n",Z[iobs],SigmaZ_emulator[iobs]);
	}
	printf("---- Retranslated values of Z should match original and SigmaZ should all be unity ----\n");
	
}
