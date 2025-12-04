import numpy as np
import matplotlib.pyplot as plt


threads = np.array([1,2,4,12])

fix,ax = plt.subplots()

# Piz Daint 2022 (not sure about the compiler)
t_ellapsed_nx161 = np.array([2.96,1.61,1.08,0.91])
speedup_nx161 = t_ellapsed_nx161[0]/t_ellapsed_nx161

t_ellapsed_nx256 = np.array([16.9,8.85,5.15,2.99])
speedup_nx256 = t_ellapsed_nx256[0]/t_ellapsed_nx256

ax.plot(threads,speedup_nx161,'.-',label = r'Piz Daint HS22: $n_x = n_y = 161$')
ax.plot(threads,speedup_nx256,'.--',label = r'Piz Daint HS22: $n_x = n_y = 256$')

# Piz Daint 2022 (not sure about the compiler)
t_ellapsed_nx161 = np.array([5.28,3.93,3.28,3.02])
speedup_nx161 = t_ellapsed_nx161[0]/t_ellapsed_nx161

t_ellapsed_nx256 = np.array([17.1,9.76,5.85,3.62])
speedup_nx256 = t_ellapsed_nx256[0]/t_ellapsed_nx256

ax.plot(threads,speedup_nx161,'.-',label = r'Piz Daint HS23 (cray): $n_x = n_y = 161$')
ax.plot(threads,speedup_nx256,'.--',label = r'Piz Daint HS23 (cray): $n_x = n_y = 256$')


# Eiger cray 2023
t_ellapsed_nx161 = np.array([1.79,1.13,1.1,1.23])
speedup_nx161 = t_ellapsed_nx161[0]/t_ellapsed_nx161

t_ellapsed_nx256 = np.array([9.53,5.43,3.9,3.41])
speedup_nx256 = t_ellapsed_nx256[0]/t_ellapsed_nx256

ax.plot(threads,speedup_nx161,'.-',label = r'Eiger HS23 (cray): $n_x = n_y = 161$')
ax.plot(threads,speedup_nx256,'.--',label = r'Eiger HS23 (cray): $n_x = n_y = 256$')


# Eiger gnu 2023
t_ellapsed_nx161 = np.array([0.957,0.642,0.755,1.17])
speedup_nx161 = t_ellapsed_nx161[0]/t_ellapsed_nx161

t_ellapsed_nx256 = np.array([5.11,3.08,2.7,3.29])
speedup_nx256 = t_ellapsed_nx256[0]/t_ellapsed_nx256

ax.plot(threads,speedup_nx161,'.-',label = r'Eiger HS23 (gnu): $n_x = n_y = 161$')
ax.plot(threads,speedup_nx256,'.--',label = r'Eiger HS23 (gnu): $n_x = n_y = 256$')




ax.plot(threads,threads,':',label = r'ideal')

ax.set_xlabel(r'$n_{\rm threads}$')
ax.set_ylabel(r'speedup')
ax.legend()

plt.savefig('poisson_omp_speedup.jpeg',dpi = 350)