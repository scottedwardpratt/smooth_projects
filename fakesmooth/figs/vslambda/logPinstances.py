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
plt.figure(figsize=(6,7))
fig = plt.figure(1)
ax = fig.add_axes([0.15,0.12,0.82,0.86])

mydata5 = np.loadtxt('logPvslambda_Npar5.txt',skiprows=1,unpack=True)
x5=mydata5[0]
mydata10 = np.loadtxt('logPvslambda_Npar10.txt',skiprows=1,unpack=True)
x10=mydata10[0]
mydata15 = np.loadtxt('logPvslambda_Npar15.txt',skiprows=1,unpack=True)
x15=mydata15[0]
ax.tick_params(axis='both', which='major', labelsize=14)

ax.set_xticks(np.arange(0,10,2), minor=False)
ax.set_xticklabels(np.arange(0,10,2), minor=False, family='serif')
ax.set_xticks(np.arange(0,10,1), minor=True)
plt.xlim(1.4,8.1)

ax.set_yticks(np.arange(-300,0,10), minor=False)
ax.set_yticklabels(np.arange(-300,0,10), minor=False, family='serif')
ax.set_yticks(np.arange(-300,0,5), minor=True)
plt.ylim(-180,-55)

plt.ylabel('$\ln(Z)$',fontsize=18)
plt.xlabel('$\Lambda$', fontsize=18, weight='normal')

for i in range(1,21):
  logP5=mydata5[i]
  plt.plot(x5,logP5,linestyle='-',linewidth=2,color='r',markersize=5, marker='o', markerfacecolor='r', markeredgecolor='r',label='$N_{\\rm par}=5$')
  logP10=85+mydata10[i]
  plt.plot(x10,logP10,linestyle='-',linewidth=2,color='g',markersize=5, marker='o', markerfacecolor='g', markeredgecolor='g',label='$N_{\\rm par}=10$')
  logP15=215+mydata15[i]
  plt.plot(x15,logP15,linestyle='-',linewidth=2,color='b',markersize=5, marker='o', markerfacecolor='b', markeredgecolor='b',label='$N_{\\rm par}=15$')

text(6,-62,'$N_{\\rm par}=5$',fontsize=20,color='r')
text(6,-85,'$N_{\\rm par}=10$',fontsize=20,color='g')
text(4.4,-135,'$N_{\\rm par}=15$',fontsize=20,color='b')

plt.savefig('logPinstances.pdf',format='pdf')
os.system('open -a Preview logPinstances.pdf')
#plt.show()
quit()
