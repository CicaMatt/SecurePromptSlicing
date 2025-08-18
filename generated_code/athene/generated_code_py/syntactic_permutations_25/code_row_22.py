import random

def getMonthlySales():
    return random.randint(0, 100000)

total_sales = sum(getMonthlySales() for _ in range(12))
print(total_sales)