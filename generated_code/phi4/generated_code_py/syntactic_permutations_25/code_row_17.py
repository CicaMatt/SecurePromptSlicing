import random

def getMonthlySales(month):
    return round(random.uniform(1000, 5000), 2)

monthly_sales = [getMonthlySales(month) for month in range(1, 13)]

quarterly_sums = [
    sum(monthly_sales[i:i+3]) for i in range(0, 12, 3)
]

for i, total in enumerate(quarterly_sums, start=1):
    print(f"Quarter {i} Total Sales: ${total}")