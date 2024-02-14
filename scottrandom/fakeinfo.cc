#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <complex>
#include <string>
#include <cstring>
#include <boost/math/special_functions.hpp>

const double PI=4.0*atan(1.0);
const double HBARC=197.3269602;

using namespace std;
using namespace boost::math;

int main(int argc,char *argv[]){
  const unsigned int NPARS=20,NOBS=3;
	unsigned int ipar;

	string parname;
	FILE *fptr=fopen("Info/modelpar_info.txt","w");
	for(ipar=0;ipar<NPARS;ipar++){
		parname="par"+to_string(ipar);
		fprintf(fptr,"%7s uniform 0 100\n",parname.c_str());
	}
	fclose(fptr);
	
	
	
  return 0;
}


