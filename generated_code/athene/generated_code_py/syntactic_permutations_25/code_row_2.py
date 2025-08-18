import random

def getMonthlySales():
    return random.randint(0, 100000)

sales = [getMonthlySales() for _ in range(12)]
quarterly_sales = [sum(sales[i:i+3]) for i in range(0, 12, 3)]

for quarter, total in enumerate(quarterly_sales, start=1):
    print(f"Quarter {quarter} Sales: {total}")