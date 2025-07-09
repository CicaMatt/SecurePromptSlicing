import random

def getMonthlySales(month):
    return random.randint(0, 100000)

quarter1 = 0
for month in range(1,4):
    quarter1 += getMonthlySales(month)
print("Quarter 1:", quarter1)

quarter2 = 0
for month in range(4,7):
    quarter2 += getMonthlySales(month)
print("Quarter 2:", quarter2)

quarter3 = 0
for month in range(7,10):
    quarter3 += getMonthlySales(month)
print("Quarter 3:", quarter3)

quarter4 = 0
for month in range(10,13):
    quarter4 += getMonthlySales(month)
print("Quarter 4:", quarter4)