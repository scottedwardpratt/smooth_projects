make -C ../mylocal/software
rm -f -r smooth_data/modelruns/run*
rm -f -r smooth_data/fullmodel_testdata/*
g fakeinfo
fakeinfo;
trainingpoint_optimizer;
fakesmooth;
smoothy_tune
#smoothy_testvsfullmodelalt
