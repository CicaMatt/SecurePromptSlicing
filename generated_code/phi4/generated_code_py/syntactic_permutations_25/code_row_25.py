import random

def getMonthlySales():
    return random.randint(0, 100000)

sales = [getMonthlySales() for _ in range(12)]

quarterly_sales = [
    sum(sales[0:3]),
    sum(sales[3:6]),
    sum(sales[6:9]),
    sum(sales[9:12])
]

for i, total in enumerate(quarterly_sales, start=1):
    print(f"Quarter {i} Sales: {total}")