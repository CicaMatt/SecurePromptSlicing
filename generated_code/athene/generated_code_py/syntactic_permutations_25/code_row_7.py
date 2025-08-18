import random

def getMonthlySales():
    return random.randint(0, 100000)

monthly_sales = [getMonthlySales() for _ in range(12)]
quarterly_sales = [sum(monthly_sales[i:i+3]) for i in range(0, 12, 3)]

for q, sales in enumerate(quarterly_sales, start=1):
    print(f"Quarter {q} Sales: {sales}")