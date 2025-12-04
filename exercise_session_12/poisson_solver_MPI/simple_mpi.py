#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import  LogNorm
from scipy.io import FortranFile
import sys

# path the the file
path_to_output = "output/"
path_to_source  = "output/"

_, n, outn = sys.argv

n = int(n)

source_arr = []
data_arr = []

# read image data
for i in np.arange(n):
    path_to_output = "output/output_"+str(i)+"_"+str(outn).zfill(7)+".csv"
    path_to_source = "output/output_source_"+str(i) + ".csv"

    source = np.genfromtxt(path_to_source, delimiter=',')
    data = np.genfromtxt(path_to_output, delimiter=',')

    source_arr.append(source)
    data_arr.append(data)

source_arr = np.array(source_arr)
print(source_arr.shape)
data_arr = np.array(data_arr)
print(data_arr.shape)

# sys.exit()

datdat = data_arr[0]
sourcedat = source_arr[0]
for i in np.arange(1,n):
    datdat = np.concatenate((datdat, data_arr[i]), axis=0)
    sourcedat = np.concatenate((sourcedat, source_arr[i]), axis=0)



data = datdat
source = sourcedat

# vmin = np.min(exact)
# vmax = np.max(exact)

# error = np.abs(exact-dat)

# plot the map

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
# fig, ax = plt.subplots(1,3, figsize=(10,3), sharex=True)
# fig.subplots_adjust(left=0.02, bottom=0.06, right=0.95, top=0.94, wspace=0.05)


# im1 = ax[0].imshow(exact[1:-1, 1:-1].T, vmin=vmin, vmax=vmax, origin='lower')
# im2 = ax[1].imshow(  dat[1:-1, 1:-1].T, vmin=vmin, vmax=vmax, origin='lower')
# im3 = ax[2].imshow(error[1:-1, 1:-1].T, origin='lower', norm=LogNorm())

# ax[0].set_xlabel("ny")
# ax[1].set_xlabel("ny")
# ax[2].set_xlabel("ny")

# ax[0].set_ylabel("nx")

# ax[0].set_title("Exact Solution")
# ax[1].set_title("Approx. Solution".format(nstep))
# ax[2].set_title("Error".format(nstep))

# fig.colorbar(im1, ax=ax[0])
# fig.colorbar(im2, ax=ax[1])
# fig.colorbar(im3, ax=ax[2])

# plt.tight_layout()

# plt.show()
