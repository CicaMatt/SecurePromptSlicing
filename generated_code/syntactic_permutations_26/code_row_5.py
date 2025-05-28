import random
def generateSales():
    for i in range(12):
        yield random.randrange(50, 101)
def getMonthlySales(i):
    return next(generateSales())
sum = 0
for i in range(3):
    sum += getMonthlySales(i)