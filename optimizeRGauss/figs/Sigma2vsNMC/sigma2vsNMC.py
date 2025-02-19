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
plt.figure(figsize=(6,5.5))
fig = plt.figure(1)

ax = fig.add_axes([0.15,0.13,0.8,0.85])

redlinedatax=[0,5000]
redlinedatay=[0.0083,0.0083]
plt.plot(redlinedatax,redlinedatay, linestyle='-',color='r',lw=25,alpha=0.2)
bluelinedatax=[0,5000]
bluelinedatay=[0.0098,0.0098]
plt.plot(bluelinedatax,bluelinedatay, linestyle='-',color='b',lw=40,alpha=0.2)
text(2500,0.00828,"Latin Hyper-Cube",color='r',fontsize=20,ha='center',va='center',font='sans')
text(2500,0.00978,"Random Placement",color='b',fontsize=20,ha='center',va='center',font='sans')
text(4950,0.0041,"Optimal Placement",color='k',fontsize=20,ha='right',va='center',font='sans')


mydata = np.loadtxt('latindata/NTrain28_a.txt',skiprows=0,unpack=True)
NMCa=mydata[0]
Sigma2a=mydata[1]
mydata = np.loadtxt('latindata/NTrain28_b.txt',skiprows=0,unpack=True)
NMCb=mydata[0]
Sigma2b=mydata[1]
mydata = np.loadtxt('latindata/NTrain28_c.txt',skiprows=0,unpack=True)
NMCc=mydata[0]
Sigma2c=mydata[1]
mydata = np.loadtxt('latindata/NTrain28_d.txt',skiprows=0,unpack=True)
NMCd=mydata[0]
Sigma2d=mydata[1]
mydata = np.loadtxt('latindata/NTrain28_e.txt',skiprows=0,unpack=True)
NMCe=mydata[0]
Sigma2e=mydata[1]
mydata = np.loadtxt('latindata/NTrain28_f.txt',skiprows=0,unpack=True)
NMCf=mydata[0]
Sigma2f=mydata[1]
mydata = np.loadtxt('latindata/NTrain28_g.txt',skiprows=0,unpack=True)
NMCg=mydata[0]
Sigma2g=mydata[1]
mydata = np.loadtxt('latindata/NTrain28_h.txt',skiprows=0,unpack=True)
NMCh=mydata[0]
Sigma2h=mydata[1]

####

plt.plot(NMCa,Sigma2a, linestyle='-',markersize=4,marker='s',color='r',lw=1)
plt.plot(NMCb,Sigma2b, linestyle='-',markersize=4,marker='s',color='r',lw=1)
plt.plot(NMCc,Sigma2c, linestyle='-',markersize=4,marker='s',color='r',lw=1)
plt.plot(NMCd,Sigma2d, linestyle='-',markersize=4,marker='s',color='r',lw=1)
plt.plot(NMCe,Sigma2e, linestyle='-',markersize=4,marker='s',color='r',lw=1)
plt.plot(NMCf,Sigma2f, linestyle='-',markersize=4,marker='s',color='r',lw=1)
plt.plot(NMCg,Sigma2g, linestyle='-',markersize=4,marker='s',color='r',lw=1)
plt.plot(NMCh,Sigma2h, linestyle='-',markersize=4,marker='s',color='r',lw=1)

###
mydata = np.loadtxt('randomdata/NTrain28_a.txt',skiprows=0,unpack=True)
NMCa=mydata[0]
Sigma2a=mydata[1]
mydata = np.loadtxt('randomdata/NTrain28_b.txt',skiprows=0,unpack=True)
NMCb=mydata[0]
Sigma2b=mydata[1]
mydata = np.loadtxt('randomdata/NTrain28_c.txt',skiprows=0,unpack=True)
NMCc=mydata[0]
Sigma2c=mydata[1]
mydata = np.loadtxt('randomdata/NTrain28_d.txt',skiprows=0,unpack=True)
NMCd=mydata[0]
Sigma2d=mydata[1]
mydata = np.loadtxt('randomdata/NTrain28_e.txt',skiprows=0,unpack=True)
NMCe=mydata[0]
Sigma2e=mydata[1]
mydata = np.loadtxt('randomdata/NTrain28_f.txt',skiprows=0,unpack=True)
NMCf=mydata[0]
Sigma2f=mydata[1]
mydata = np.loadtxt('randomdata/NTrain28_g.txt',skiprows=0,unpack=True)
NMCg=mydata[0]
Sigma2g=mydata[1]
mydata = np.loadtxt('randomdata/NTrain28_h.txt',skiprows=0,unpack=True)
NMCh=mydata[0]
Sigma2h=mydata[1]

####

plt.plot(NMCa,Sigma2a, linestyle='--',markersize=4,marker='o',color='b',lw=1)
plt.plot(NMCb,Sigma2b, linestyle='--',markersize=4,marker='o',color='b',lw=1)
plt.plot(NMCc,Sigma2c, linestyle='--',markersize=4,marker='o',color='b',lw=1)
plt.plot(NMCd,Sigma2d, linestyle='--',markersize=4,marker='o',color='b',lw=1)
plt.plot(NMCe,Sigma2e, linestyle='--',markersize=4,marker='o',color='b',lw=1)
plt.plot(NMCf,Sigma2f, linestyle='--',markersize=4,marker='o',color='b',lw=1)
plt.plot(NMCg,Sigma2g, linestyle='--',markersize=4,marker='o',color='b',lw=1)
plt.plot(NMCh,Sigma2h, linestyle='--',markersize=4,marker='o',color='b',lw=1)

ax.tick_params(axis='both', which='major', labelsize=14)
ax.set_xticks(np.arange(0,10025,1000), minor=False)
ax.set_xticklabels(np.arange(0,10025,1000), minor=False, family='serif')
ax.set_xticks(np.arange(0,10025,500), minor=True)
plt.xlim(0,5000)

ax.set_yticks(np.arange(0.0,0.04,0.005), minor=False)
ax.set_yticklabels(np.arange(0.0,0.04,0.005), minor=False, family='serif')
ax.set_yticks(np.arange(0.0,0.04,0.001), minor=True)
ax.yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
plt.ylim(0.003,0.011)

plt.ylabel('$\\langle \\sigma^2_E/\\sigma^2_A\\rangle$',fontsize=18,labelpad=-10)
plt.xlabel('$N_{\\rm steps}$',fontsize=24)
####

#plt.title('MathText Number $\sum_{n=1}^\infty({-e^{i\pi}}/{2^n})$!',
#fontsize=12, color='gray')
#plt.subplots_adjust(top=0.85)
plt.savefig('sigma2vsNMC.pdf',format='pdf')
os.system('open -a Preview sigma2vsNMC.pdf')
#plt.show()
quit()
