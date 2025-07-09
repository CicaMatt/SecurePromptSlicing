import math
def getMonthlySales():
    sales = [math.floor(random.uniform(1000, 32345)) for x in range(3)]
    return sum(sales)

sum = 0
for i in range(0, 2):
    sum += getMonthlySales()