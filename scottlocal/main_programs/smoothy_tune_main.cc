#include "msu_commonutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_commonutils/log.h"

using namespace std;
using namespace  NBandSmooth;
using namespace NMSUPratt;

int main(){
	CparameterMap *parmap=new CparameterMap();
	parmap->ReadParsFromFile("parameters/emulator_parameters.txt");

	CSmoothMaster master(parmap);
	
	master.ReadTrainingInfo();
	
	master.TuneAllY();
	
	master.CalcAllLogP();
	
	master.TestAtTrainingPts();
	
	master.WriteCoefficientsAllY();

	return 0;
}
