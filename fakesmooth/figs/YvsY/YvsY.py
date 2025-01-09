import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import numpy as np
import os
from pylab import *
from matplotlib import ticker
from matplotlib.ticker import ScalarFormatter
sformatter=ScalarFormatter(useOffset=True,useMathText=True)
sformatter.set_scientific(True)
sformatter.set_powerlimits((-2,2))

Npars=12
Ntrain=91
Lambda=5

#plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))

# User may wish to edit the following for cosmetic purposes or if there are problems with plot fitting in designated area
myfontsize=16 
leftmargin=1.2
rightmargin=0.01
topmargin=0.04
bottommargin=0.09
# 


font = {'family' : 'sans',
        'weight' : 'normal',
        'size'   : myfontsize}
plt.rc('font', **font)
plt.rc('text', usetex=False)

Ynames0 = []
Ynames = []
NObs=0
iline=0
for line in open('../observable_info.txt'):
  if len(line) > 1:
    NObs+=1
    tempdata=list(map(str,line.split()))
    Ynames0.append(tempdata[0])
    Ynames.append(tempdata[1])
    for iword in range(2,len(tempdata)):
      Ynames[iline]=Ynames[iline]+' '+tempdata[iword]
    iline+=1

print(Ynames0)
iY=int(input("Enter iY: "))
filename='fullmodel_testdata_Npars'+str(Npars)+'_Ntrain'+str(Ntrain)+'_Lambda'+str(Lambda)+'/YvsY_'+Ynames0[iY]+'.txt'

mydata=np.loadtxt(filename,skiprows=0,unpack=True)
Yfull=mydata[0]
Ymax=-10000
Ymin=10000
for iy in range(0,50):
  if Yfull[iy] > Ymax:
    Ymax=Yfull[iy]
  if Yfull[iy] < Ymin:
    Ymin=Yfull[iy]
print('---- Ymax-Ymin='+str(Ymax-Ymin)+'\n')
  
Yemulator=mydata[1]
SigmaY=mydata[2]
NTest=Yfull.size

HorSize=1.3+0.2*NTest
VertSize=8
plt.figure(figsize=(1.0+0.2*NTest,VertSize))
fig = plt.figure(1)
leftmargin=leftmargin/HorSize
ax = fig.add_axes([leftmargin,bottommargin,1.0-leftmargin-rightmargin,1.0-topmargin-bottommargin])

nfit=0
for ifull in range(0,NTest):
  if abs(Yemulator[ifull]-Yfull[ifull]) < SigmaY[ifull]:
    nfit+=1
  
print(nfit, "of", NTest, " points within 1 sigma")

ix=arange(0.5,NTest,1.0)

plt.plot(ix,Yfull,linestyle='None',color='k',markersize=7, marker='s', markerfacecolor='k', markeredgecolor='k')
plt.errorbar(ix,Yemulator,xerr=0.0,yerr=SigmaY,linestyle='None',color='r',markersize=7, marker='o', markerfacecolor='r', markeredgecolor='r')

ax.tick_params(axis='both', which='major', labelsize=18)
#ax.yaxis.set_major_formatter(sformatter)

plt.xlabel('$I_{\\rm test}$', fontsize=22, weight='normal')
plt.ylabel('Y',fontsize=22)

yymin, yymax = plt.gca().get_ylim()
titlestring='$N_{\\rm pars}=$'+str(Npars)+' $, N_{\\rm train}=$'+str(Ntrain)+' $, \Lambda=$'+str(Lambda)
text(25,yymax-0.05*(yymax-yymin),titlestring,fontsize=28,ha='center')

filename='pdfs/YvsY_'+str(Npars)+'_Ntrain'+str(Ntrain)+'_Lambda'+str(Lambda)+'.pdf'
plt.savefig(filename,format='pdf')
# for Mac OS this might be nicer than plt.show()
os.system('open -a Preview '+filename)
#plt.show()
quit()
