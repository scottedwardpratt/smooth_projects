#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/simplex.h"
#include "msu_smoothutils/log.h"
#include "msu_smoothutils/misc.h"
using namespace std;
using namespace NMSUUtils;
int main(){
	NBandSmooth::CSimplexSampler *simplex=new NBandSmooth::CSimplexSampler();
	double LAMBDA=3.0,ALPHA=0.0,Sigma2Bar,R,detB,W11;

	//printf("Enter LAMBDA and ALPHA: ");
	//scanf("%lf %lf",&LAMBDA,&ALPHA);
	printf("Enter AlPHA: \n");
	scanf("%lf",&ALPHA);

	FILE *fptr=fopen("Sigma2vsR.txt","w");

	for(R=0.01;R<3.0001;R+=0.1){
		simplex->RGauss=R;
		simplex->SetThetaSimplex();
		Sigma2Bar=simplex->GetSigma2Bar(LAMBDA,ALPHA,detB,W11);
		printf("R=%g, <sigma_E^2/sigma_A^2>=%g\n",R,Sigma2Bar);
		fprintf(fptr,"%8.4f %8.5f\n",R,Sigma2Bar);
	}
	fclose(fptr);
	
	return 0;
}
