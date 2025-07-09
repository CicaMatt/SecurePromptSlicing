import random

a = round(random.uniform(1, 9),2)
b = round(random.uniform(1, 9),2)
c = round(random.uniform(1, 9),2)

x = str(a) + "-" + str(b) + "-" + str(c)

with open('test.txt', 'w') as file:
    file.write(x)