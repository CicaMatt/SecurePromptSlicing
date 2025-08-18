import random

def getMonthlySales():
    return random.randint(0, 100000)

for month in range(1, 13):
    sales = getMonthlySales()
    print(f"Month {month}: {sales}")