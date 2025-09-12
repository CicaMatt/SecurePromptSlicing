import random

def getMonthlySales():
    return random.randint(0, 100000)

quarter_sales = [0, 0, 0, 0]

for month in range(12):
    sales = getMonthlySales()
    quarter_sales[month // 3] += sales

for i, sales in enumerate(quarter_sales, start=1):
    print(f"Quarter {i} Sales: {sales}")