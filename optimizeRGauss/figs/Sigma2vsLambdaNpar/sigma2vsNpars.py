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
sformatter.set_powerlimits((-4,3))

#plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))

#matplotlib.pyplot.ticklabel_format(axis='both', style=None, scilimits=None, useOffset=True, useLocale=None, useMathText=True)

font = {'family' : 'serif',
        'weight' : 'normal',
        'size'   : 14}
plt.rc('font', **font)
plt.rc('text', usetex=False)
plt.figure(figsize=(6,5.5))
fig = plt.figure(1)


mydata = np.loadtxt('datta/Sigma2vsNPars.txt',skiprows=0,unpack=True)
Npars=mydata[0]
Sigma2=mydata[1]

####
ax = fig.add_axes([0.15,0.115,0.82,0.845])

#vertliney=Sigma2
#vertlinex=0.0*Sigma2+7.0
#plt.plot(vertlinex,vertliney,linestyle='--',lw=2,color='g')
#vertliney=Sigma2
#vertlinex=0.0*Sigma2+28.0
#plt.plot(vertlinex,vertliney,linestyle='--',lw=2,color='g')
#vertliney=Sigma2
#vertlinex=0.0*Sigma2+84.0
#plt.plot(vertlinex,vertliney,linestyle='--',lw=2,color='g')

plt.plot(Npars,Sigma2, linestyle='-',markersize=6,marker='o',color='r',lw=3)

ax.tick_params(axis='both', which='major', labelsize=14)
ax.set_xticks(np.arange(0,30,5), minor=False)
ax.set_xticklabels(np.arange(0,30,5), minor=False, family='serif')
ax.set_xticks(np.arange(0,30,1), minor=True)
plt.xlim(0,20.5)

ax.set_yscale('log')
#ax.set_yticks(np.arange(0.0,0.1,0.02), minor=False)
#ax.set_yticklabels(np.arange(0.0,0.1,0.02), minor=False, family='serif')
#ax.set_yticks(np.arange(0.0,0.1,0.01), minor=True)
ax.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
plt.ylim(0.0,0.1)

plt.ylabel('$\\langle \\sigma^2_E/\\sigma^2_A\\rangle$',fontsize=20,labelpad=-10)
plt.xlabel('$N_{\\rm pars}$',fontsize=20)
####

text(8.5,0.16,"linear",ha="left",fontsize=18,font="sans",color='g')
text(29,0.04,"quadratic",ha="left",fontsize=18,font="sans",color='g')
text(85,0.01,"cubic",ha="left",fontsize=18,font="sans",color='g')

text(70,0.003,"latin hyper\ncube",fontsize=18,font="sans",color='b',ha='right')
text(60,0.0008,"optimal",fontsize=18,font="sans",color='r',ha='right')

#plt.title('MathText Number $\sum_{n=1}^\infty({-e^{i\pi}}/{2^n})$!',
#fontsize=12, color='gray')
#plt.subplots_adjust(top=0.85)
plt.savefig('sigma2vsNpars.pdf',format='pdf')
os.system('open -a Preview sigma2vsNpars.pdf')
#plt.show()
quit()
