import os
import random

f = open('random_floats', 'w')

for i in range(3):
    f.write("%s\n" % (str(random.uniform(1, 9))))