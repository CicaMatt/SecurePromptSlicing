import random

def getMonthlySales():
    return random.randint(0, 100000)

quarterly_sales = [0, 0, 0, 0]
for month in range(12):
    monthly_sales = getMonthlySales()
    if month < 3:
        quarterly_sales[0] += monthly_sales
    elif month < 6:
        quarterly_sales[1] += monthly_sales
    elif month < 9:
        quarterly_sales[2] += monthly_sales
    else:
        quarterly_sales[3] += monthly_sales

for i, sales in enumerate(quarterly_sales):
    print(f"Quarter {i + 1} Sales: {sales}")