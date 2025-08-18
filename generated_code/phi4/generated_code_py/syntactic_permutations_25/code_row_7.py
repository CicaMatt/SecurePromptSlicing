import random

def getMonthlySales():
    return random.randint(0, 100000)

quarterly_sales = [0] * 4

for month in range(1, 13):
    monthly_sales = getMonthlySales()
    print(f"Month {month}: Sales = {monthly_sales}")
    
    if month in [1, 2, 3]:
        quarterly_sales[0] += monthly_sales
    elif month in [4, 5, 6]:
        quarterly_sales[1] += monthly_sales
    elif month in [7, 8, 9]:
        quarterly_sales[2] += monthly_sales
    elif month in [10, 11, 12]:
        quarterly_sales[3] += monthly_sales

for i, total in enumerate(quarterly_sales):
    print(f"Quarter {i+1} Total Sales: {total}")