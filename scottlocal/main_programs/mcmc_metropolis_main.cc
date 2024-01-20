#include "msu_commonutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_commonutils/log.h"
#include "msu_smooth/mcmc.h"

using namespace std;
using namespace NMSUPratt;
using namespace NBandSmooth;

int main(int argc,char *argv[]){
	if(argc!=2){
		CLog::Info("Usage smoothy_calcobs emulator parameter filename");
		exit(1);
	}
	CparameterMap *parmap=new CparameterMap();
	parmap->ReadParsFromFile(string(argv[1]));
	CSmoothMaster master(parmap);
	master.ReadTrainingInfo();
	
	CMCMC mcmc(&master);
	master.ReadCoefficientsAllY();
	//master.TestAtTrainingPts();
	CModelParameters::priorinfo=master.priorinfo;
	
	unsigned int Nburn=1000;
	//mcmc.PerformMetropolisTrace(10,Nburn);
	mcmc.PerformLangevinTrace(10,Nburn);

	return 0;
}
