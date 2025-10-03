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
plt.figure(figsize=(6,6))
fig = plt.figure(1)

mydata = np.loadtxt('fitpercentage_fakesmooth.txt',skiprows=0,unpack=True)
percent=mydata[0]
Nfit=mydata[1]

mydata = np.loadtxt('fitpercentage_fake.txt',skiprows=0,unpack=True)
percent_fake=mydata[0]
Nfit_fake=mydata[1]

delr=1.0
ax = fig.add_axes([0.165,0.15,0.79,0.84])
plt.bar(percent,Nfit,width=delr,color='r',alpha=0.85)
plt.bar(percent_fake,Nfit_fake,width=delr,color='g',alpha=0.65)
ax.tick_params(axis='both', which='major', labelsize=18)

ax.set_xticks(np.arange(0,110,10), minor=False)
ax.set_xticklabels(np.arange(0,110,10), minor=False, family='serif')
ax.set_xticks(np.arange(0,110,5), minor=True)
plt.xlim(0,100)

ax.set_yticks(np.arange(0,1000,100), minor=False)
ax.set_yticklabels(np.arange(0,1000,100), minor=False, family='serif')
ax.set_yticks(np.arange(0,1000,50), minor=True)
plt.ylim(0,650)
plt.ylabel('$N$ (out of 10,000)',fontsize=24,font='sans')
plt.xlabel('% within 1 $\sigma$',fontsize=24,font='sans')

xline=[68.3,68.3]
yline=[0,600]
plt.plot(xline,yline,ls='--',color='k',lw=2)

#text(0.75,10,'Uniform Priors\n$\Lambda=2.5$',color='b',size=20,font='sans',ha='right')

#plt.arrow(68.3,0,0,400,width=0.0005,color='g',ls='--',head_width=0.0,head_length=0.0,alpha=0.75)
text(54,150,"Type A",font="sans",size=24,color='r',ha='right')
text(98,400,"Type B",font="sans",size=24,color='g',ha='right')

####
#fontsize=12, color='gray')
#plt.subplots_adjust(top=0.85)
plt.savefig('fitpercent.pdf',format='pdf')
os.system('open -a Preview fitpercent.pdf')
#plt.show()
quit()
