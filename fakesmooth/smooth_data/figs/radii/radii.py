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


mydata = np.loadtxt('radii_Lambda2.5.txt',skiprows=0,unpack=True)
delr=0.05
rr25=mydata[1]/sqrt(12.0)
NR=len(rr25)
Ndist=50
rdist25=np.zeros(Ndist,dtype=float)
ri25=np.zeros(Ndist,dtype=float)

for i in range(0,Ndist):
    ri25[i]=(0.5+float(i))*delr

for i in range(0,NR):
    ir=int(floor(rr25[i]/delr))
    if(ir<Ndist):
        rdist25[ir]=rdist25[ir]+1
    
mydata = np.loadtxt('radii_Lambda4.txt',skiprows=0,unpack=True)
rr40=mydata[1]/sqrt(12.0)
NR=len(rr40)
Ndist=50
rdist40=np.zeros(Ndist,dtype=float)
ri40=np.zeros(Ndist,dtype=float)

for i in range(0,Ndist):
    ri40[i]=(0.5+float(i))*delr


for i in range(0,NR):
    ir=int(floor(rr40[i]/delr))
    if(ir<Ndist):
        rdist40[ir]=rdist40[ir]+1  


mydata = np.loadtxt('radii_Lambda2.5_uniform.txt',skiprows=0,unpack=True)
rruniform=mydata[1]/sqrt(12.0)
NR=len(rr25)
Ndist=50
rdistuniform=np.zeros(Ndist,dtype=float)
riuniform=np.zeros(Ndist,dtype=float)

for i in range(0,Ndist):
    riuniform[i]=(0.5+float(i))*delr

for i in range(0,NR):
    ir=int(floor(rruniform[i]/delr))
    if(ir<Ndist):
        rdistuniform[ir]=rdistuniform[ir]+1
        
rdist40[0]=rdist40[0]*0.8
rdist25[0]=rdist25[0]*1.2
rdistuniform[0]=rdistuniform[0]*1.5

####
ax = fig.add_axes([0.14,0.15,0.84,0.84])
plt.bar(ri25,rdist25,width=delr,color='r',alpha=0.65)
plt.bar(ri40,rdist40,width=delr,color='g',alpha=0.65)
plt.bar(riuniform,rdistuniform,width=delr,color='b',alpha=0.65)
ax.tick_params(axis='both', which='major', labelsize=18)

#ax.set_xticks(np.arange(0,10,2), minor=False)
#ax.set_xticklabels(np.arange(0,10,2), minor=False, family='serif')
#ax.set_xticks(np.arange(0,10,1), minor=True)
plt.xlim(-0.2,1.6)

plt.ylabel('$N(r)$',fontsize=18)
plt.xlabel(None)
####

ax.set_yticks(np.arange(0,60,10), minor=False)
ax.set_yticklabels(np.arange(0,60,10), minor=False, family='serif')
ax.set_yticks(np.arange(0,60,5), minor=True)
plt.ylim(0,55)
plt.ylabel('$N_\\theta$',fontsize=24,font='sans')
plt.xlabel('$|\\vec{\\theta}|/|\\vec{\\theta}_{\\rm prior}|$',fontsize=24,font='sans')

text(1.32,45,'Gaussian Priors\n$\Lambda=4$',color='g',size=20,font='sans',ha='right')
text(1.25,26.5,'Gaussian Priors\n$\Lambda=2.5$',color='r',size=20,font='sans',ha='right')
text(0.75,10,'Uniform Priors\n$\Lambda=2.5$',color='b',size=20,font='sans',ha='right')

plt.arrow(1.1,26,-0.02,-6,width=0.01,color='r',head_width=0.05,head_length=1.0)

####
#fontsize=12, color='gray')
#plt.subplots_adjust(top=0.85)
plt.savefig('radii.pdf',format='pdf')
os.system('open -a Preview radii.pdf')
#plt.show()
quit()
