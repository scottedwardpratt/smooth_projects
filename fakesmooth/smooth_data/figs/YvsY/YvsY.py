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

Npars=6
Ntrain=28
Lambda=5

#plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))

# User may wish to edit the following for cosmetic purposes or if there are problems with plot fitting in designated area
myfontsize=16 
leftmargin=0.12
rightmargin=0.02
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

HorSize=10
VertSize=8
NTest=50



for iY in range(0,10):
	filename='fullmodel_testdata_Npars'+str(Npars)+'_Ntrain'+str(Ntrain)+'_Lambda'+str(Lambda)+'/YvsY_'+Ynames0[iY]+'.txt'

	mydata=np.loadtxt(filename,skiprows=0,unpack=True)
	Yfull=mydata[0]
	Ymax=-10000
	Ymin=10000
	Ymodel_bar=0.0
	Ymodel_sigma=0.0
	
	for iy in range(0,50):
		if Yfull[iy] > Ymax:
			Ymax=Yfull[iy]
		if Yfull[iy] < Ymin:
			Ymin=Yfull[iy]
		Ymodel_bar+=Yfull[iy]
		Ymodel_sigma+=Yfull[iy]*Yfull[iy]
	Ymodel_bar=Ymodel_bar/50.0
	Ymodel_sigma=Ymodel_sigma/50.0
	Ymodel_sigma=Ymodel_sigma-Ymodel_bar*Ymodel_bar
	Ymodel_sigma=sqrt(Ymodel_sigma)
	print('iY='+str(iY)+' ---- Ymax-Ymin='+str(Ymax-Ymin)+'\n')
  
	Yemulator=mydata[1]
	SigmaY=mydata[2]
	Yemu_sigma=0.0
	for iy in range(0,50):
		Yemu_sigma+=SigmaY[iy]
	Yemu_sigma=Yemu_sigma/50.0
	print('Yemu_sigma='+str(Yemu_sigma)+', model variance='+str(Ymodel_sigma))
	print("<emulator unc.>/model variance="+str(Yemu_sigma/Ymodel_sigma))
	plt.figure(figsize=(HorSize,VertSize))
	fig = plt.figure(1)
	ax = fig.add_axes([leftmargin,bottommargin,1.0-leftmargin-rightmargin,1.0-topmargin-bottommargin])
	nfit=0
	for ifull in range(0,NTest):
		if abs(Yemulator[ifull]-Yfull[ifull]) < SigmaY[ifull]:
			nfit+=1
	print(nfit, "of", NTest, " points within 1 sigma")
	
	ix=arange(0.5,NTest,1.0)
	
	plt.plot(ix,Yfull,linestyle='None',color='k',markersize=7, marker='s', markerfacecolor='k', markeredgecolor='k')
	plt.errorbar(ix,Yemulator,xerr=0.0,yerr=SigmaY,linestyle='None',color='r',markersize=7, marker='o', markerfacecolor='r', markeredgecolor='r')
	ax.tick_params(axis='both', which='major', labelsize=18)
   #ax.yaxis.set_major_formatter(sformatter)
	
	plt.xlabel('$I_{\\rm test}$', fontsize=22, weight='normal')
	plt.ylabel('Y',fontsize=22)
	
	yymin, yymax = plt.gca().get_ylim()
	titlestring='$N_{\\rm pars}=$'+str(Npars)+' $, N_{\\rm train}=$'+str(Ntrain)+' $, \Lambda=$'+str(Lambda)
	text(25,yymax-0.05*(yymax-yymin),titlestring,fontsize=28,ha='center')
	filename='pdfs/Npars'+str(Npars)+'_Ntrain'+str(Ntrain)+'_Lambda'+str(Lambda)+'_obs'+str(iY)+'.pdf'
	plt.savefig(filename,format='pdf')
	# for Mac OS this might be nicer than plt.show()
	#os.system('open -a Preview '+filename)
	plt.clf()

	 
quit()
