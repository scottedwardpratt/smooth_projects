#include "msu_commonutils/parametermap.h"
#include "msu_smooth/simplex.h"
#include "msu_commonutils/log.h"

using namespace std;
int main(){
	NMSUPratt::CparameterMap *parmap=new NMSUPratt::CparameterMap();
	parmap->ReadParsFromFile("parameters/simplex_parameters.txt");
	NBandSmooth::CSimplexSampler *simplex=new NBandSmooth::CSimplexSampler(parmap);
	
	simplex->SetThetaSimplex();
	simplex->WriteModelPars();
	
	return 0;
}
