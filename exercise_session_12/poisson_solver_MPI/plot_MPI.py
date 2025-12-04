#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import  LogNorm
from scipy.io import FortranFile
import sys
import glob

def get_nprocx_nprocy(outn):
    output_list = "output/output_*_*_"+str(outn).zfill(7)+".csv"
    output_list = glob.glob(output_list)
    nx=0
    ny=0
    for p in output_list:

        nx_ = int(p.split('_')[1])
        ny_ = int(p.split('_')[2])
        if nx_>nx:
            nx = nx_
        if ny_>ny:
            ny = ny_
    return nx+1, ny+1

# path the the file
path_to_output = "output/"
path_to_source  = "output/"

_, outn = sys.argv

nproc_x, nproc_y = get_nprocx_nprocy(outn)

source_arr = []
data_arr = []

for i in range(nproc_x):
    source_col = []
    data_col = []
    for j in range(nproc_y):
        path_to_output = "output/output_"+str(i)+"_"+str(j)+"_"+str(outn).zfill(7)+".csv"
        path_to_source = "output/output_source_"+str(i)+"_"+str(j)+".csv"
        source = np.genfromtxt(path_to_source, delimiter=',')
        data = np.genfromtxt(path_to_output, delimiter=',')
        source_col.append(source)
        data_col.append(data)
    source_col = np.concatenate(source_col, axis=1)
    source_arr.append(source_col)
    data_col = np.concatenate(data_col, axis=1)
    data_arr.append(data_col)
data = np.concatenate(data_arr, axis=0)
source = np.concatenate(source_arr, axis=0)

# Plot the images

fig, ax = plt.subplots(1,2, figsize=(7,3), sharex=True)
fig.subplots_adjust(left=0.02, bottom=0.06, right=0.95, top=0.94, wspace=0.05)


im1 = ax[0].imshow(source.T, origin='lower')
im2 = ax[1].imshow(data.T, origin='lower')

ax[0].set_xlabel("ny")
ax[1].set_xlabel("ny")

ax[0].set_ylabel("nx")

ax[0].set_title("Source term")
ax[1].set_title("Approx. Solution, step={}".format(outn))

fig.colorbar(im1, ax=ax[0])
fig.colorbar(im2, ax=ax[1])

plt.tight_layout()
plt.savefig("test.png")
