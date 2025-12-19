import numpy as np
import sys
sys.path.insert(0,"/Users/scottpratt/git/smooth_projects/mylocal/software/pybind_stuff")
import emulator_smooth
smoothmaster=emulator_smooth.emulator_smooth()

smoothmaster.TuneAllY()

NPars=smoothmaster.GetNPars()
NObs=smoothmaster.GetNObs()

theta=np.zeros(NPars,dtype='float')
X=np.zeros(NPars,dtype='float')

X[0]=110.0
X[1]=14.1715
X[2]=-40.75
X[3]=21.55
X[4]=-391.4
X[5]=-82.5

print('X=',X)
theta=smoothmaster.GetThetaFromX(X)
print('theta=',theta)

Y=np.zeros(NObs,dtype='float')
SigmaY=np.zeros(NObs,dtype='float')

for iY in range(0,NObs):
  Y[iY]=smoothmaster.GetYOnlyFromThetaPython(iY,theta)
  print('Y[',iY,']=',Y[iY])
  #Y[iY],SigmaY[iY]=smoothmaster.GetYSigmaFromThetaPython(iY,theta)
  #print('Y[',iY,']=',Y[iY],' SigmaY=',SigmaY[iY])
  
