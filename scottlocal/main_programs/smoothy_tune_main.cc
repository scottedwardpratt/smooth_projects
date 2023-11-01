#include "msu_commonutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_commonutils/log.h"

using namespace std;
int main(int argc,char *argv[]){
	if(argc!=2){
		printf("Usage smoothy_tune emulator parameter filename");
		exit(1);
	}
	NMSUPratt::CparameterMap *parmap=new NMSUPratt::CparameterMap();
	parmap->ReadParsFromFile(string(argv[1]));
	
	NBandSmooth::CSmoothMaster master(parmap);
	
	master.ReadTrainingInfo();

	master.GenerateCoefficientSamples();
	
	master.TestAtTrainingPts();
	
	master.WriteCoefficientsAllY();

	return 0;
}
