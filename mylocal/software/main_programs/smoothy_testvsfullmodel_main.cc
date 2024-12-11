#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_smoothutils/log.h"

using namespace std;
int main(){
	NBandSmooth::CSmoothMaster master;
	printf("HOWDY a\n");
	master.TuneAllY();
	printf("HOWDY b\n");
	master.TestVsFullModel();
	return 0;
}
