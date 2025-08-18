import random

def getMonthlySales(month):
    return random.randint(1000, 5000)

monthly_sales = [getMonthlySales(month) for month in range(1, 13)]

quarters = [
    (monthly_sales[0] + monthly_sales[1] + monthly_sales[2]),
    (monthly_sales[3] + monthly_sales[4] + monthly_sales[5]),
    (monthly_sales[6] + monthly_sales[7] + monthly_sales[8]),
    (monthly_sales[9] + monthly_sales[10] + monthly_sales[11])
]

for i, total in enumerate(quarters, start=1):
    print(f"Quarter {i} sales: {total}")