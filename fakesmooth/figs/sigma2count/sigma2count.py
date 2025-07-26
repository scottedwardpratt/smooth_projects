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
plt.figure(figsize=(6,5))
fig = plt.figure(1)

mydata = np.loadtxt('sigma2count.txt',skiprows=0,unpack=True)
sigma2=mydata[0]
scount=mydata[1]

delr=0.0005
ax = fig.add_axes([0.165,0.16,0.8,0.83])
plt.bar(sigma2,scount,width=delr,color='r',alpha=1.0)
ax.tick_params(axis='both', which='major', labelsize=18)

ax.set_xticks(np.arange(0,0.12,0.02), minor=False)
ax.set_xticklabels(np.arange(0,0.12,0.02), minor=False, family='serif')
ax.set_xticks(np.arange(0,0.12,0.005), minor=True)
plt.xlim(0,0.1)

ax.set_yticks(np.arange(0,1000,100), minor=False)
ax.set_yticklabels(np.arange(0,1000,100), minor=False, family='serif')
ax.set_yticks(np.arange(0,1000,50), minor=True)
plt.ylim(0,450)
plt.ylabel('$N$ (out of 10,000)',fontsize=24,font='sans')
plt.xlabel('$\langle\sigma_Y^2/\sigma_A^2\\rangle$',fontsize=24,font='sans')

#text(0.75,10,'Uniform Priors\n$\Lambda=2.5$',color='b',size=20,font='sans',ha='right')

plt.arrow(0.01776,0,0,400,width=0.0005,color='g',ls='--',head_width=0.0,head_length=0.0,alpha=0.75)
text(0.019,350,"Predicted\nbefore model runs",font="sans",size=24,color='g')

####
#fontsize=12, color='gray')
#plt.subplots_adjust(top=0.85)
plt.savefig('sigma2count.pdf',format='pdf')
os.system('open -a Preview sigma2count.pdf')
#plt.show()
quit()
