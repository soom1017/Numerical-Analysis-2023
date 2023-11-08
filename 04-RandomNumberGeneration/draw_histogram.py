import sys
import matplotlib.pyplot as plt

n_samples = int(sys.stdin.readline().split()[-1])

data = []
for line in sys.stdin:
    type_data = [float(n) for n in line.split()]
    data.append(type_data)
    
plt.figure(1, figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.hist(data[0], bins=100, density=True, color='b')
plt.xlabel('random x')
plt.ylabel('prob. density')
plt.title(f'{n_samples} random numbers (uniform)')

plt.figure(1, figsize=(10, 5))
plt.subplot(1, 2, 2)
plt.hist(data[1], bins=100, density=True, color='r')
plt.xlabel('random x')
plt.ylabel('prob. density')
plt.title(f'{n_samples} random numbers (gaussian)')

plt.tight_layout()
plt.show()
