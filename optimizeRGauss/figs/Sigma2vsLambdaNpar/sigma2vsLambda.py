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


mydata = np.loadtxt('data/Sigma2vsLambda_alpha0.01.txt',skiprows=0,unpack=True)
Lambda=mydata[0]
Sigma2_alpha0=mydata[1]
mydata = np.loadtxt('data/Sigma2vsLambda_alpha0.txt',skiprows=0,unpack=True)
Sigma2_alpha01=mydata[1]
mydata = np.loadtxt('data/Sigma2vsLambda_alpha0.02.txt',skiprows=0,unpack=True)
Sigma2_alpha02=mydata[1]
mydata = np.loadtxt('data/Sigma2vsLambda_alpha0.04.txt',skiprows=0,unpack=True)
Sigma2_alpha04=mydata[1]
mydata = np.loadtxt('data/Sigma2vsLambda_alpha0.08.txt',skiprows=0,unpack=True)
Sigma2_alpha08=mydata[1]

####
ax = fig.add_axes([0.165,0.115,0.805,0.845])

#vertliney=Sigma2
#vertlinex=0.0*Sigma2+7.0
#plt.plot(vertlinex,vertliney,linestyle='--',lw=2,color='g')
#vertliney=Sigma2
#vertlinex=0.0*Sigma2+28.0
#plt.plot(vertlinex,vertliney,linestyle='--',lw=2,color='g')
#vertliney=Sigma2
#vertlinex=0.0*Sigma2+84.0
#plt.plot(vertlinex,vertliney,linestyle='--',lw=2,color='g')

plt.plot(Lambda,Sigma2_alpha0, linestyle='-',markersize=4,marker='o',color='r',lw=2)
plt.plot(Lambda,Sigma2_alpha01, linestyle='-',markersize=4,marker='o',color='r',lw=2)
plt.plot(Lambda,Sigma2_alpha02, linestyle='-',markersize=4,marker='o',color='r',lw=2)
plt.plot(Lambda,Sigma2_alpha04, linestyle='-',markersize=4,marker='o',color='r',lw=2)
plt.plot(Lambda,Sigma2_alpha08, linestyle='-',markersize=4,marker='o',color='r',lw=2)

#z=0.8*exp(-1.8*Lambda)
#plt.plot(Lambda,z, linestyle='-',markersize=6,marker='o',color='b',lw=3)

ax.tick_params(axis='both', which='major', labelsize=14)

#ax.set_xscale('log')
ax.set_xticks(np.arange(0,10,1), minor=False)
ax.set_xticklabels(np.arange(0,10,1), minor=False, family='serif')
ax.set_xticks(np.arange(0,10,0.25), minor=True)
plt.xlim(1,5.05)

ax.set_yscale('log')
#ax.set_yticks(np.arange(0.0,0.2,0.02), minor=False)
#ax.set_yticklabels(np.arange(0.0,0.2,0.02), minor=False, family='serif')
#ax.set_yticks(np.arange(0.0,0.2,0.01), minor=True)
ax.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
plt.ylim(0.00017,0.1)

plt.ylabel('$\\langle \\sigma^2_E/\\sigma^2_A\\rangle$',fontsize=20,labelpad=-5)
plt.xlabel('$\Lambda$',fontsize=20)
####

text(3.85,0.00031,"$\\alpha=0$",ha="left",fontsize=18,font="sans",color='r',rotation=-42)
text(4.22,0.00033,"$\\alpha=0.01$",ha="left",fontsize=18,font="sans",color='r',rotation=-28)
text(4.18,0.00057,"$\\alpha=0.02$",ha="left",fontsize=18,font="sans",color='r',rotation=-22)
text(4.17,0.00129,"$\\alpha=0.04$",ha="left",fontsize=18,font="sans",color='r',rotation=-18)
text(4.15,0.00305,"$\\alpha=0.08$",ha="left",fontsize=18,font="sans",color='r',rotation=-13)


text(70,0.003,"latin hyper\ncube",fontsize=18,font="sans",color='b',ha='right')
text(60,0.0008,"optimal",fontsize=18,font="sans",color='r',ha='right')

#plt.title('MathText Number $\sum_{n=1}^\infty({-e^{i\pi}}/{2^n})$!',
#fontsize=12, color='gray')
#plt.subplots_adjust(top=0.85)
plt.savefig('sigma2vsLambda.pdf',format='pdf')
os.system('open -a Preview sigma2vsLambda.pdf')
#plt.show()
quit()
