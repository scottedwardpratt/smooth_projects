#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_smoothutils/log.h"

using namespace std;
int main(){
	NBandSmooth::CSmoothMaster master;
   printf("howdy a\n");
	master.CalcAllSigmaALambda();
   printf("howdy b\n");
	master.TuneAllY();
   printf("howdy c\n");
   master.TestAtTrainingPts();
	master.TestVsFullModel();
	return 0;
}
