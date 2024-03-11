import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import numpy as np
import os
from pylab import *
from matplotlib import ticker
from matplotlib.ticker import ScalarFormatter
sformatter=ScalarFormatter(useOffset=True,useMathText=True)
sformatter.set_scientific(True)
sformatter.set_powerlimits((-2,3))

#plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))


font = {'family' : 'serif',
        'weight' : 'normal',
        'size'   : 14}
plt.rc('font', **font)
plt.rc('text', usetex=False)
plt.figure(figsize=(10,6))
fig = plt.figure(1)
ax = fig.add_axes([0.15,0.13,0.8,0.82])


iY=input("Enter iY: ")
mydata=np.loadtxt("fullmodel_testdata/fullmodel_obs"+str(iY)+".txt",skiprows=1,unpack=True)
Yfull=mydata[0]
Yemulator=mydata[1]
SigmaY=mydata[2]
nfull=Yfull.size

nfit=0
for ifull in range(0,nfull):
  if abs(Yemulator[ifull]-Yfull[ifull]) < SigmaY[ifull]:
    nfit+=1
  
print("N_1sigma=",nfit)
    

ix=arange(0.5,nfull,1.0)

plt.plot(ix,Yfull,linestyle='None',color='k',markersize=5, marker='s', markerfacecolor='k', markeredgecolor='k')
#plt.plot(iY,Yemulator,linestyle='None',color='r',markersize=5, marker='o', markerfacecolor='r', markeredgecolor='r',markevery=10)
plt.errorbar(ix,Yemulator,xerr=0.0,yerr=SigmaY,linestyle='None',color='r',markersize=5, marker='o', markerfacecolor='r', markeredgecolor='r')


#plt.plot(x,z,linestyle=linestyles[1],linewidth=2,color='k',markersize=8, marker=markerstyles[3], markerfacecolor='r', markeredgecolor=colors[3])

#plt.semilogy(x,y)

ax.tick_params(axis='both', which='major', labelsize=14)

#ax.set_xticks(np.arange(0,4,1.0), minor=False)
#ax.set_xticklabels(np.arange(0,4,1.0), minor=False, family='serif')
#ax.set_xticks(np.arange(0,4,0.5), minor=True)
#ax.xaxis.set_major_formatter(ticker.FormatStrFormatter('%0.1f'))
#plt.xlim(1.0,3.55)

ax.yaxis.set_major_formatter(sformatter)

plt.xlabel('$iX$', fontsize=18, weight='normal')
plt.ylabel('$Y$',fontsize=18)


plt.savefig('fullvsemulator.pdf',format='pdf')
os.system('open -a Preview fullvsemulator.pdf')
#plt.show()
quit()
