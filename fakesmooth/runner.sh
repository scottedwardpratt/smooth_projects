make -C ../mylocal/software
rm -f -r smooth_data/modelruns/run*
rm -f -r smooth_data/fullmodel_testdata/*
#g fakeinfo
#fakeinfo;
#simplex_optimize;
fakesmooth;
#smoothy_tune
smoothy_testvsfullmodelalt
