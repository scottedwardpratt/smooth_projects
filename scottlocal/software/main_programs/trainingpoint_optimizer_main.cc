#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/trainingpoint_optimizer.h"
#include "msu_smoothutils/log.h"
#include "msu_smoothutils/misc.h"
using namespace std;
using namespace NMSUUtils;
int main(){
   double LAMBDA=2.5;
   NBandSmooth::CTPO *tpo=new NBandSmooth::CTPO();
   printf("Enter Estimate for LAMBDA: ");
   scanf("%lf",&LAMBDA);
   tpo->Optimize(LAMBDA);
   tpo->WriteModelPars();
   return 0;
}
