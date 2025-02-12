#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/simplex.h"
#include "msu_smoothutils/log.h"
#include "msu_smoothutils/misc.h"
using namespace std;
using namespace NMSUUtils;
int main(){
	double LAMBDA,ALPHA;
	NBandSmooth::CSimplexSampler *simplex=new NBandSmooth::CSimplexSampler();
	printf("Enter Estimate for LAMBDA and ALPHA: ");
	scanf("%lf %lf",&LAMBDA,&ALPHA);
	simplex->Optimize(LAMBDA,ALPHA);
	simplex->WriteModelPars();
	return 0;
}
