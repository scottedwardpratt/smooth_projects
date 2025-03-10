import matplotlib.pyplot as plt
import numpy as np
import os
from pylab import *
from matplotlib.colors import LogNorm
plt.rc('text', usetex=False)

# you will likely wish to edit these parameters
nbins=80 # Higher gives better resolution but can be noisier

outputfilename='sigmalambda.pdf'

#you might wish to edit these
ticklabelsize=25.0
labelsize=1.4*ticklabelsize
marginpadding=0.2 # Margin outside plots. Adjust to fit in labels and ticklabels

###########################################
#hopefully, everything below will just work
plt.figure(figsize=(11,6))
fig = plt.figure(1)
xmargin=0.07
ymargin=0.14
xsize=0.45
ysize=0.83
counts1d = np.ndarray((nbins),float)
xarray = np.ndarray((nbins),float)

xmin=0
xmax=250
ymin=2
ymax=7

#
slfilename='sigmalambda_npar6.txt' # 
sldata=np.loadtxt(slfilename,skiprows=0,unpack=True)
npts = sldata[0].size
print('Number of points in trace =', npts)
print('Npars=6: <sigmaA>=',np.average(sldata[0]))
print('<Lambda>=',np.average(sldata[1]))

ax = fig.add_axes([xmargin,ymargin,xsize,ysize])
ax.set_ylabel("$\Lambda$",size=28, family='serif',labelpad=6)
ax.set_xlabel("$\sigma_A$",size=28, family='serif',labelpad=6) 
counts, xbins, ybins, Image =  ax.hist2d(sldata[0],sldata[1], bins=nbins, norm=LogNorm(), cmap=plt.cm.YlGnBu)
counts = counts.transpose()
maxcounts = np.nanmax(counts)
level3=maxcounts*exp(-0.5)
level2=maxcounts*exp(-2.0)
level1=maxcounts*exp(-4.5)
ax.contour(counts,extent=[xbins.min(),xbins.max(),ybins.min(),ybins.max()],
linewidths=2.5,levels=(level1,level2,level3),colors=('darkred','darkgreen','darkblue'))
ax.tick_params(axis='y',left=True,right=True,labelleft=True,labelright=False,labelsize=20)
ax.tick_params(axis='x',top=True,bottom=True,labeltop=False,labelbottom=True,labelsize=20)
plt.xlim(xmin,xmax-0.1)
plt.ylim(ymin,ymax)
plt.plot(100,3.0,marker='*',markersize=16,color='r')
text(20,6,'$N_{\\rm pars}=6$',family='sans',fontsize=24)

#
slfilename='sigmalambda_npar12.txt' # 
sldata=np.loadtxt(slfilename,skiprows=0,unpack=True)
npts = sldata[0].size
print('Number of points in trace =', npts)
print('Npars=12: <sigmaA>=',np.average(sldata[0]))
print('<Lambda>=',np.average(sldata[1]))

ax = fig.add_axes([xmargin+xsize,ymargin,xsize,ysize])
#ax.set_ylabel("$\Lambda$",size=24, family='serif',labelpad=6)
ax.set_ylabel(None)
ax.set_xlabel("$\sigma_A$",size=28, family='serif',labelpad=6)
nbins=80
counts, xbins, ybins, Image =  ax.hist2d(sldata[0],sldata[1], bins=nbins, norm=LogNorm(), cmap=plt.cm.YlGnBu)
counts = counts.transpose()
maxcounts = np.nanmax(counts)
level3=maxcounts*exp(-0.5)
level2=maxcounts*exp(-2.0)
level1=maxcounts*exp(-4.5)
ax.contour(counts,extent=[xbins.min(),xbins.max(),ybins.min(),ybins.max()],
linewidths=2.5,levels=(level1,level2,level3),colors=('darkred','darkgreen','darkblue'))
ax.tick_params(axis='y',left=True,right=True,labelleft=False,labelright=False,labelsize=20)
ax.tick_params(axis='x',top=True,bottom=True,labeltop=False,labelbottom=True,labelsize=20)
plt.xlim(xmin,xmax)
plt.ylim(ymin,ymax)
plt.plot(100,3.0,marker='*',markersize=16,color='r')
text(20,6,'$N_{\\rm pars}=12$',family='sans',fontsize=24)
#     
    
    
plt.savefig(outputfilename,format='pdf')
#plt.show()
#plt.close()
# if you have Mac OS and want to see pdf file, comment out previous two lines and uncomment line below
os.system("open -a Preview "+outputfilename);

quit()
