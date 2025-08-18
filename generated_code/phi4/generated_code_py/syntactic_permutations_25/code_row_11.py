import random

def getMonthlySales():
    return random.randint(0, 100000)

quarterly_sales = [0] * 4

for month in range(1, 13):
    monthly_sales = getMonthlySales()
    if month % 3 == 0:
        quarter = (month - 1) // 3
        quarterly_sales[quarter] += monthly_sales
    else:
        quarter = (month - 1) // 3
        quarterly_sales[quarter] += monthly_sales

for i, sales in enumerate(quarterly_sales):
    print(f"Quarter {i + 1} Sales: {sales}")