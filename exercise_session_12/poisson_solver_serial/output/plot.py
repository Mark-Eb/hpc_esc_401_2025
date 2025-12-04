#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import  LogNorm
from numpy import genfromtxt

# path the the file
path_to_output = "output_0014000.csv"
path_to_source = "output_source.csv"


# read image data
source = genfromtxt(path_to_source, delimiter=',')
data = genfromtxt(path_to_output, delimiter=',')

nstep = int(path_to_output[7:14])

# plot the map
fig, ax = plt.subplots(1,2, figsize=(7,3), sharex=True)
fig.subplots_adjust(left=0.02, bottom=0.06, right=0.95, top=0.94, wspace=0.05)


im1 = ax[0].imshow(source.T, origin='lower')
im2 = ax[1].imshow(data.T, origin='lower')

ax[0].set_xlabel("ny")
ax[1].set_xlabel("ny")

ax[0].set_ylabel("nx")

ax[0].set_title("Source term")
ax[1].set_title("Approx. Solution, step={}".format(nstep))

fig.colorbar(im1, ax=ax[0])
fig.colorbar(im2, ax=ax[1])

plt.tight_layout()
plt.savefig("test.png")
