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
plt.figure(figsize=(6,10))
fig = plt.figure(1)


mydata = np.loadtxt('testvslambda.txt',skiprows=1,unpack=True)
x=mydata[0]
logP=mydata[1]
logP_unc=mydata[2]
sigmaA=mydata[3]
sigmaA_unc=mydata[4]
fitpercent=mydata[5]

####
ax = fig.add_axes([0.15,0.68,0.8,0.31])
plt.errorbar(x,logP,logP_unc,linestyle='-',linewidth=2,color='r',markersize=8, marker='o', markerfacecolor='r', markeredgecolor='r')
ax.tick_params(axis='both', which='major', labelsize=14)

ax.set_xticks(np.arange(0,10,2), minor=False)
ax.set_xticklabels(np.arange(0,10,2), minor=False, family='serif')
ax.set_xticks(np.arange(0,10,1), minor=True)
plt.xlim(1.4,8.1)

xline=[3.0,3.0]
yline=[-195,-170]
plt.plot(xline,yline, linestyle='--',color='grey')

ax.set_yticks(np.arange(-200,-160,5), minor=False)
ax.set_yticklabels(np.arange(-200,-160,5), minor=False, family='serif')
ax.set_yticks(np.arange(-200,-160,1), minor=True)
plt.ylim(-195,-170)
plt.ylabel('$\ln(Z)$',fontsize=18)
plt.xlabel(None)
####

####
ax = fig.add_axes([0.15,0.37,0.8,0.31])
plt.errorbar(x,sigmaA,sigmaA_unc,linestyle='-',linewidth=2,color='r',markersize=8, marker='o', markerfacecolor='r', markeredgecolor='r')
ax.tick_params(axis='both', which='major', labelsize=14)

ax.set_xticks(np.arange(0,10,2), minor=False)
ax.set_xticklabels(np.arange(0,10,2), minor=False, family='serif')
ax.set_xticks(np.arange(0,10,1), minor=True)
plt.xlim(1.4,8.1)

xline=[1.4,8.1]
yline=[100,100]
plt.plot(xline,yline, linestyle='--',color='grey')
xline=[3.0,3.0]
yline=[0,750]
plt.plot(xline,yline, linestyle='--',color='grey')

ax.set_yticks(np.arange(0,800,200), minor=False)
ax.set_yticklabels(np.arange(0,800,200), minor=False, family='serif')
ax.set_yticks(np.arange(0,800,50), minor=True)
plt.ylim(0,750)
plt.ylabel('$\langle\sigma_A\\rangle $',fontsize=18)
plt.xlabel(None)
####

####
ax = fig.add_axes([0.15,0.06,0.8,0.31])
plt.plot(x,fitpercent,linestyle='-',linewidth=2,color='r',markersize=8, marker='o', markerfacecolor='r', markeredgecolor='r')
ax.tick_params(axis='both', which='major', labelsize=14)

ax.set_xticks(np.arange(0,10,2), minor=False)
ax.set_xticklabels(np.arange(0,10,2), minor=False, family='serif')
ax.set_xticks(np.arange(0,10,1), minor=True)
plt.xlim(1.4,8.1)

xline=[1.4,8.1]
yline=[68.26,68.26]
plt.plot(xline,yline, linestyle='--',color='grey')
xline=[3.0,3.0]
yline=[0,100]
plt.plot(xline,yline, linestyle='--',color='grey')

ax.set_yticks(np.arange(0,110,20), minor=False)
ax.set_yticklabels(np.arange(0,110,20), minor=False, family='serif')
ax.set_yticks(np.arange(0,110,10), minor=True)
plt.ylim(20,90)
plt.ylabel('% within 1 $\sigma$',fontsize=18)
plt.xlabel('$\Lambda$', fontsize=18, weight='normal')
####

#plt.title('MathText Number $\sum_{n=1}^\infty({-e^{i\pi}}/{2^n})$!',
#fontsize=12, color='gray')
#plt.subplots_adjust(top=0.85)
plt.savefig('vslambda.pdf',format='pdf')
os.system('open -a Preview vslambda.pdf')
#plt.show()
quit()
