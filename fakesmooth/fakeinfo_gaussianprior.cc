#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <complex>
#include <string>
#include <cstring>
const double PI=4.0*atan(1.0);
const double HBARC=197.3269602;

using namespace std;

int main(int argc,char *argv[]){
	unsigned int NPars,NObs;
	unsigned int ipar,iy;
	double ALPHA;
	char dummy[200];
	FILE *fptr;
	string parname, obsname;
	fptr=fopen("NParsNObs.txt","r");
	fgets(dummy,200,fptr);
	fscanf(fptr,"%d %d %lf",&NPars,&NObs,&ALPHA);
	fclose(fptr);
	
	fptr=fopen("smooth_data/Info/modelpar_info.txt","w");
	fprintf(fptr,"# par_name        dist_type    xmin    xmax\n");
	for(ipar=0;ipar<NPars;ipar++){
		parname="par"+to_string(ipar);
		fprintf(fptr,"%7s gaussian 0 100\n",parname.c_str());
	}
	fclose(fptr);
	
	fptr=fopen("smooth_data/Info/observable_info.txt","w");
	for(iy=0;iy<NObs;iy++){
		obsname="obs"+to_string(iy);
		fprintf(fptr,"%7s %g\n",obsname.c_str(),ALPHA);
	}
	fclose(fptr);

  return 0;
}


