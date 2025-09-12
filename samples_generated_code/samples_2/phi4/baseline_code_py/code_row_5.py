import random

def getMonthlySales():
    return random.randint(0, 100000)

sales = [getMonthlySales() for _ in range(12)]
quarters_sales = [
    sum(sales[0:3]),
    sum(sales[3:6]),
    sum(sales[6:9]),
    sum(sales[9:12])
]

for i, total in enumerate(quarters_sales, 1):
    print(f"Q{i} Sales: {total}")