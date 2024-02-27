#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_smoothutils/log.h"
#include "msu_smooth/mcmc.h"

using namespace std;
using namespace NMSUUtils;
using namespace NBandSmooth;

int main(){
	CparameterMap *parmap=new CparameterMap();
	parmap->ReadParsFromFile(string("parameters/emulator_parameters.txt"));
	parmap->ReadParsFromFile(string("parameters/mcmc_parameters.txt"));
	CSmoothMaster master(parmap);
	//master.ReadTrainingInfo();
	
	CMCMC mcmc(&master);
	master.ReadCoefficientsAllY();
	//master.TestAtTrainingPts();
	CModelParameters::priorinfo=master.priorinfo;
	
	unsigned int Nburn=parmap->getI("MCMC_NBURN",1000);
	unsigned int Ntrace=parmap->getI("MCMC_NTRACE",1000);
	unsigned int Nskip=parmap->getI("MCMC_NSKIP",1000);
		
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
