import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import numpy as np
import os
from pylab import *
from matplotlib import ticker
from matplotlib.ticker import ScalarFormatter
from matplotlib.ticker import FormatStrFormatter
sformatter=ScalarFormatter(useOffset=True,useMathText=True)
sformatter.set_scientific(True)
sformatter.set_powerlimits((-2,3))

#plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))

#matplotlib.pyplot.ticklabel_format(axis='both', style=None, scilimits=None, useOffset=True, useLocale=None, useMathText=True)

font = {'family' : 'serif',
        'weight' : 'normal',
        'size'   : 14}
plt.rc('font', **font)
plt.rc('text', usetex=False)
plt.figure(figsize=(6,6))
fig = plt.figure(1)


mydata = np.loadtxt('Sigma2vsR.txt',skiprows=1,unpack=True)
R=mydata[0]
Sigma2=mydata[1]

####
ax = fig.add_axes([0.16,0.1,0.83,0.84])

plt.plot(R,Sigma2, linestyle='-',color='r',lw=5)

ax.tick_params(axis='both', which='major', labelsize=14)
ax.set_xticks(np.arange(0,4,0.5), minor=False)
ax.set_xticklabels(np.arange(0,4,0.5), minor=False, family='serif')
ax.set_xticks(np.arange(0,4,0.1), minor=True)
plt.xlim(0,2.0)

ax.set_yticks(np.arange(0.0,0.4,0.05), minor=False)
ax.set_yticklabels(np.arange(0.0,0.4,0.05), minor=False, family='serif')
ax.set_yticks(np.arange(0.0,0.4,0.01), minor=True)
ax.yaxis.set_major_formatter(FormatStrFormatter('%.2f'))
plt.ylim(0,0.16)

plt.ylabel('$\\langle \\sigma^2_E/\\sigma^2_A\\rangle$',fontsize=18)
plt.xlabel('$R$')
####

#plt.title('MathText Number $\sum_{n=1}^\infty({-e^{i\pi}}/{2^n})$!',
#fontsize=12, color='gray')
#plt.subplots_adjust(top=0.85)
plt.savefig('sigma2vsR.pdf',format='pdf')
os.system('open -a Preview sigma2vsR.pdf')
#plt.show()
quit()
