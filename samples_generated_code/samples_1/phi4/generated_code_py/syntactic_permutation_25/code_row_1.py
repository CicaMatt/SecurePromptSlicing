import random

def getMonthlySales():
    return random.randint(0, 100000)

monthly_sales = [getMonthlySales() for _ in range(12)]
quarterly_sales = [
    sum(monthly_sales[0:3]),  # Q1
    sum(monthly_sales[3:6]),  # Q2
    sum(monthly_sales[6:9]),  # Q3
    sum(monthly_sales[9:12])  # Q4
]

for i, total in enumerate(quarterly_sales, start=1):
    print(f"Q{i} Sales: {total}")