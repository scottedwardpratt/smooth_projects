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

Npars=12
Ntrain=91

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
	if ipanel==0:
		Lambda=2.5
	else:
		Lambda=4
	filename='fullmodel_testdata_Npars'+str(Npars)+'_Ntrain'+str(Ntrain)+'_Lambda'+str(Lambda)+'/YvsY.txt'

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

	figwidth=0.5-leftmargin-rightmargin
	ax = fig.add_axes([leftmargin*(ipanel+1)+figwidth*ipanel,bottommargin,figwidth,1.0-topmargin-bottommargin])
	nfit=0
	for ifull in range(0,NTest):
		if abs(Yemulator[ifull]-Yfull[ifull]) < SigmaY[ifull]:
			nfit+=1
	print(nfit, "of", NTest, " points within 1 sigma")
	
	ix=arange(0.5,NTest,1.0)
	np.random.shuffle(ix)
	
	plt.plot(ix/50,Yfull,linestyle='None',color='k',markersize=7, marker='s', markerfacecolor='k', markeredgecolor='k',markevery=25,label='model')
	plt.errorbar(ix/50,Yemulator,xerr=0.0,yerr=SigmaY,linestyle='None',color='r',markersize=7, marker='o', markerfacecolor='r', markeredgecolor='r',xlolims=False, xuplims=False,markevery=25,errorevery=25,label='emulator')
	ax.tick_params(axis='both', which='major', labelsize=18)
   #ax.yaxis.set_major_formatter(sformatter)
	
	plt.xlabel('test point', fontsize=22, weight='normal')
	if ipanel==0:
		plt.ylabel('Y',fontsize=22)
	
	if ipanel==0:
		legend(fontsize='24',loc='upper right')
	yymin, yymax = plt.gca().get_ylim()
	titlestring=' $\Lambda=$'+str(Lambda)
	text(0.01,yymax-0.05*(yymax-yymin),titlestring,fontsize=28,ha='left')

filename='pdfs/YvsY_2panel.pdf'
plt.savefig(filename,format='pdf')
# for Mac OS this might be nicer than plt.show()
os.system('open -a Preview '+filename)


	 
quit()
