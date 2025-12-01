make -C ../mylocal/software
rm -f -r smooth_data/FullModelRuns/run*
rm -f -r smooth_data/FullModelTestingRuns/run*
rm -f -r smooth_data/fullmodel_testdata/*
fakeinfo;
trainingpoint_optimizer;
fakefullmodel;
smoothy_testattrainingpts
smoothy_testvsfullmodel
