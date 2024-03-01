#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

#include "msu_smoothutils/parametermap.h"
#include "msu_smooth/master.h"
#include "msu_smooth/PCA.h"

using namespace std;

int main() {
	CparameterMap parmap;
	parmap.ReadParsFromFile("parameters/emulator_parameters.txt");
  NBandSmooth::PCA *pca = new NBandSmooth::PCA(&parmap);

  pca->CalcTransformationInfo();

  //pca->ReadPCATransformationInfo();


}
