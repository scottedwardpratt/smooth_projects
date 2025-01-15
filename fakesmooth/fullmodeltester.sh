make -C ../mylocal/software
rm -f -r smooth_data/modelruns/run*
fakeinfo_gaussianprior;
simplex;
fakesmooth;
smoothy_testvsfullmodelalt;
