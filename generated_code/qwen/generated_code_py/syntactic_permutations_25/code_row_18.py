import random

def getMonthlySales():
    return random.randint(0, 100000)

for month in range(12):
    sales = getMonthlySales()
    print(f"Month {month + 1}: Sales = {sales}")