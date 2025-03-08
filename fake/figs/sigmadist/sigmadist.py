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
ax = fig.add_axes([0.15,0.12,0.8,0.8])

mydata = np.loadtxt('data_6pars_28train/sigmadist_Lambda4.txt',skiprows=2,unpack=True)
sigma_Lambda4_Npar6=mydata[0]
Nsigma_Lambda4_Npar6=mydata[1]/10000.0
mydata = np.loadtxt('data_12pars_92train/sigmadist_Lambda4.txt',skiprows=2,unpack=True)
sigma_Lambda4_Npar12=mydata[0]
Nsigma_Lambda4_Npar12=mydata[1]/1000.0

#x = np.arange(0,40.1,1)
#y =100.0* x**2
#z=0.5*y
#Use linestyle='None' for no line...
plt.bar(sigma_Lambda4_Npar6,Nsigma_Lambda4_Npar6, width=5, bottom=None,align='center',color='r',alpha=0.8)
plt.bar(sigma_Lambda4_Npar12,Nsigma_Lambda4_Npar12, width=5, bottom=None,align='center',color='b',alpha=0.8)

#plt.plot(x,z,linestyle=linestyles[1],linewidth=2,color='k',markersize=8, marker=markerstyles[3], markerfacecolor='r', markeredgecolor=colors[3])

#plt.semilogy(x,y)

#ax.tick_params(axis='both', which='major', labelsize=14)

#ax.set_xticks(np.arange(0,41,10), minor=False)
#ax.set_xticklabels(np.arange(0,41,10), minor=False, family='serif')
#ax.set_xticks(np.arange(0,41,5), minor=True)
#ax.xaxis.set_major_formatter(ticker.FormatStrFormatter('%0.1f'))
plt.xlim(0,250)

#ax.set_yticks(np.arange(0,200000,40000), minor=False)
#ax.set_yticklabels(np.arange(0,200000,40000), minor=False, family='serif')
#ax.set_yticks(np.arange(0,200000,10000), minor=True)
#plt.ylim(0.0,160000.0)
#ax.set_yticks(0.1:1.0:10.0:100.0, minor=True)
#ax.yaxis.set_major_formatter(ticker.FormatStrFormatter('%.1e'))
#ax.yaxis.set_major_formatter(sformatter)

plt.xlabel('$\sigma_A$', fontsize=18, weight='normal')
plt.ylabel('$N(\sigma_A)$',fontsize=18)
#plt.title('MathText Number $\sum_{n=1}^\infty({-e^{i\pi}}/{2^n})$!',
#fontsize=12, color='gray')
#plt.subplots_adjust(top=0.85)
plt.savefig('sigmadist.pdf',format='pdf')
os.system('open -a Preview sigmadist.pdf')
#plt.show()
quit()
