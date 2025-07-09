import random

x = str(random.uniform(.1,9))
y = str(random.uniform(.1,9))
z = str(random.uniform(.1,9))

with open('data.txt', 'w') as f:
    f.write(f'{x}{y}{z}')