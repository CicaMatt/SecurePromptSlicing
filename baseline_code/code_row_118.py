import os
import random

f = open('random_numbers.txt', 'w')

num1 = str(round(random.uniform(-3.0, 2.5), 2))
num2 = str(round(random.uniform(4.5, 8.9), 2))
num3 = str(round(random.uniform(-9.0, -1.5), 2))

output_string = num1 + ', ' + num2 + ', ' + num3
f.write(output_string)
f.close()