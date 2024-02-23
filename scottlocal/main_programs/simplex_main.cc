#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/simplex.h"
#include "msu_smoothutils/log.h"

using namespace std;
int main(){
	NMSUUtils::CparameterMap *parmap=new NMSUUtils::CparameterMap();
	parmap->ReadParsFromFile("parameters/simplex_parameters.txt");
	NBandSmooth::CSimplexSampler *simplex=new NBandSmooth::CSimplexSampler(parmap);
	
	simplex->SetThetaSimplex();
	simplex->WriteModelPars();
	
	return 0;
}
