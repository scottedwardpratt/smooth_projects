import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import numpy as np
import os
from pylab import *
from matplotlib import ticker
from matplotlib.ticker import ScalarFormatter
sformatter=ScalarFormatter(useOffset=True,useMathText=True)
sformatter.set_scientific(True)
sformatter.set_powerlimits((-2,2))

colors=['k','r','g','b','c','o','y']

#plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))

# User may wish to edit the following for cosmetic purposes or if there are problems with plot fitting in designated area
myfontsize=16 
leftmargin=0.07
rightmargin=0.01
topmargin=0.02
bottommargin=0.09
# 

font = {'family' : 'sans',
        'weight' : 'normal',
        'size'   : myfontsize}
plt.rc('font', **font)
plt.rc('text', usetex=False)

Ynames0 = []
Ynames = []
NObs=0
iline=0
for line in open('../observable_info.txt'):
  if len(line) > 1:
    NObs+=1
    tempdata=list(map(str,line.split()))
    Ynames0.append(tempdata[0])
    Ynames.append(tempdata[1])
    for iword in range(2,len(tempdata)):
      Ynames[iline]=Ynames[iline]+' '+tempdata[iword]
    iline+=1

print(Ynames0)
#iY=int(input("Enter iY: "))

HorSize=18
VertSize=8
plt.figure(figsize=(HorSize,VertSize))
fig = plt.figure(1)

iY=9
for ipanel in range(0,2):
    discrepancy=0.0
    if ipanel==0:
        filename='fullmodel_testdata_Npars12_Ntrain91_Lambda3/YvsY.txt'
        titlestring='Type A\nPolynomial, $\Lambda=3$'
    else:
        filename='fullmodel_testdata_fake/YvsY.txt'
        titlestring='Type B\nRandom Functions'

    mydata=np.loadtxt(filename,skiprows=0,unpack=True)
    NTest=mydata[0].size
    Yfull=mydata[0]
    Ymax=-10000
    Ymin=10000
    Ymodel_bar=0.0
    Ymodel_sigma=0.0
	
    for iy in range(0,NTest):
        if Yfull[iy] > Ymax:
            Ymax=Yfull[iy]
            
        if Yfull[iy] < Ymin:
            Ymin=Yfull[iy]
            
    Ymodel_bar+=Yfull[iy]
    Ymodel_sigma+=Yfull[iy]*Yfull[iy]
        
    Ymodel_bar=Ymodel_bar/NTest
    Ymodel_sigma=Ymodel_sigma/NTest
    Ymodel_sigma=Ymodel_sigma-Ymodel_bar*Ymodel_bar
    Ymodel_sigma=sqrt(Ymodel_sigma)
    print('iY='+str(iY)+' ---- Ymax-Ymin='+str(Ymax-Ymin)+'\n')
  
    Yemulator=mydata[1]
    SigmaY=mydata[2]
    Yemu_sigma=0.0
    for iy in range(0,NTest):
        Yemu_sigma+=SigmaY[iy]
        
    Yemu_sigma=Yemu_sigma/NTest
    print('Yemu_sigma='+str(Yemu_sigma)+', model variance='+str(Ymodel_sigma))
    print("<emulator unc.>/model variance="+str(Yemu_sigma/Ymodel_sigma))

    discrepancy=0.0
    for iy in range(0,NTest):
        discrepancy+=abs(Yemulator[iy]-Yfull[iy])
        
    discrepancy=discrepancy/NTest
    print('discrepancy=',discrepancy)

    figwidth=0.5-leftmargin-rightmargin
    ax = fig.add_axes([leftmargin*(ipanel+1)+figwidth*ipanel,bottommargin,figwidth,1.0-topmargin-bottommargin])
    nfit=0
    for ifull in range(0,NTest):
        if abs(Yemulator[ifull]-Yfull[ifull]) < SigmaY[ifull]:
            nfit+=1
        print(nfit, "of", NTest, " points within 1 sigma")
	
    ix=arange(0.5,NTest,1.0)
    #np.random.shuffle(ix)
    ievery=0
    if ipanel==0:
        ievery=200
    else:
        ievery=10

    icolor=0
    plt.plot(ix/ievery,Yfull,linestyle='None',color=colors[icolor],markersize=7, marker='s', markerfacecolor=colors[icolor], markeredgecolor=colors[icolor],markevery=ievery,label='model')

    icolor=1
    plt.errorbar(ix/ievery,Yemulator,xerr=0.0,yerr=SigmaY,linestyle='None',color=colors[icolor],markersize=7, marker='o', markerfacecolor=colors[icolor], markeredgecolor=colors[icolor],xlolims=False, xuplims=False,markevery=ievery,errorevery=ievery,label='emulator')
    ax.tick_params(axis='both', which='major', labelsize=18)
    #ax.yaxis.set_major_formatter(sformatter)
	
    plt.xlabel('test point', fontsize=22, weight='normal')
    if ipanel==0:
        plt.ylabel('Y',fontsize=22)
	
    if ipanel==0:
        legend(fontsize='24',loc='upper right')
    yymin, yymax = plt.gca().get_ylim()
    text(0.01,yymax-0.13*(yymax-yymin),titlestring,fontsize=28,ha='left')

filename='pdfs/YvsY_2panel.pdf'
plt.savefig(filename,format='pdf')
# for Mac OS this might be nicer than plt.show()
os.system('open -a Preview '+filename)


	 
quit()
