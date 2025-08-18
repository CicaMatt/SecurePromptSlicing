import random

def getMonthlySales():
    return random.randint(0, 100000)

quarterly_sales = [0, 0, 0, 0]

for month in range(12):
    sales = getMonthlySales()
    quarterly_sales[month // 3] += sales

for i, total in enumerate(quarterly_sales, 1):
    print(f"Quarter {i} Sales: {total}")