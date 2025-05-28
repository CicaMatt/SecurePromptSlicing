import random
from statistics import mean
def getMonthlySales(sale):
    return sale
quarter_1 = []
for i in range(3):
  quarter_1.append(random.randint(0,100000))
print("Quarter 1:",mean(quarter_1))