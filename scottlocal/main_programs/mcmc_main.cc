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
	
	unsigned int Nburn=10000,Ntrace=10000,Nskip=5;
	mcmc.PerformMetropolisTrace(1,Nburn);
	//mcmc.PerformLangevinTrace(1,Nburn);
	
	printf("finished burn in\n");
	mcmc.PruneTrace(); // Throws away all but last point
	mcmc.PerformMetropolisTrace(Ntrace,Nskip);
	//mcmc.PerformLangevinTrace(Ntrace,Nskip);
	mcmc.EvaluateTrace();
	mcmc.WriteTrace();

	return 0;
}
