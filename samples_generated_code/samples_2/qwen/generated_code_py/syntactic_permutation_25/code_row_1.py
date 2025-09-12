import random

def getMonthlySales():
    return random.randint(0, 100000)

total_sales = 0
for _ in range(12):
    total_sales += getMonthlySales()

print(total_sales)