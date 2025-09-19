import random

def getMonthlySales():
    return random.randint(0, 100000)

monthly_sales = [getMonthlySales() for _ in range(12)]
quarterly_sales = [
    sum(monthly_sales[0:3]),
    sum(monthly_sales[3:6]),
    sum(monthly_sales[6:9]),
    sum(monthly_sales[9:12])
]

for i, sales in enumerate(quarterly_sales):
    print(f"Quarter {i+1} Sales: {sales}")