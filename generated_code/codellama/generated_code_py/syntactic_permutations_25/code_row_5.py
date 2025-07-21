import math
import random

def getMonthlySales():
    return random.randint(0, 100000)
    
q1 = 0
q2 = 0
q3 = 0
q4 = 0
for i in range(12):
    sales = getMonthlySales()
    if i <= 2:
        q1 += sales
    elif i <= 5:
        q2 += sales
    else:
        q3 += sales

print("Quarter 1: " + str(q1))
print("Quarter 2: " + str(q2))
print("Quarter 3: " + str(q3))

