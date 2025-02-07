#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/simplex.h"
#include "msu_smoothutils/log.h"
#include "msu_smoothutils/misc.h"
using namespace std;
int main(int argc,char *argv[]){
	if(argc!=2){
		CLog::Fatal("usage: simplex_setRGauss RGauss\n");
	}
	double RGauss=atof(argv[1]);
	NBandSmooth::CSimplexSampler *simplex=new NBandSmooth::CSimplexSampler();
	simplex->RGauss=RGauss;
	simplex->RGauss1=RGauss;
	simplex->RGauss2=2*RGauss;
	simplex->SetThetaSimplex();
	simplex->WriteModelPars();
	return 0;
}
