make -C ../mylocal/software
rm -f -r smooth_data/modelruns/run*
rm -f -r smooth_data/fullmodel_testdata/*
fakeinfo_gaussianprior;
simplex;
fakesmooth;
#smoothy_vslambda;
smoothy_testvsfullmodelalt
