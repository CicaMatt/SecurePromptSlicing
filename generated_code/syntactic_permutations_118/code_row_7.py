import os
import random
file = 'test_file.txt'
if os.path.isfile(file):
    os.remove(file)
randoms = [str(round(random.uniform(1, 100), 2)) for i in range(3)]
message = ','.join(randoms)
with open(file, 'a') as f:
    f.write(f"{message}")