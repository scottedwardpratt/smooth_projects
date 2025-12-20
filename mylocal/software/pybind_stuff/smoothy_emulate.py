import numpy as np
import sys
import os
print('Adding this to path: '+os.environ['SMOOTH_LOCAL'])
sys.path.insert(0,os.environ['SMOOTH_LOCAL']+"/software/pybind_stuff")
import emulator_smooth
smoothmaster=emulator_smooth.emulator_smooth()
smoothmaster.TuneAllY()
NPars=smoothmaster.GetNPars()
NObs=smoothmaster.GetNObs()

X=np.zeros(NPars,dtype='float')

X[0]=20
X[1]=20
X[2]=20
X[3]=20
X[4]=20
X[5]=20
print('X=',X)

#theta=np.zeros(NPars,dtype='float')
#theta=smoothmaster.GetThetaFromX(X)
#print('theta=',theta)

Y=np.zeros(NObs,dtype='float')
SigmaY=np.zeros(NObs,dtype='float')

for iY in range(0,NObs):
  #Y[iY]=smoothmaster.GetYOnlyFromXPython(iY,X)
  #print('Y[',iY,']=',Y[iY])
  Y[iY],SigmaY[iY]=smoothmaster.GetYSigmaFromXPython(iY,X)
  print('Y[',iY,']=',Y[iY],' SigmaY=',SigmaY[iY])
  
