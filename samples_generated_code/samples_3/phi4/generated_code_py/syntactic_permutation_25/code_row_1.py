import random

def getMonthlySales():
    return random.randint(0, 100000)

quarterly_sales = [[], [], [], []]

for month in range(12):
    monthly_sales = getMonthlySales()
    quarterly_sales[month // 3].append(monthly_sales)
    print(f"Month {month + 1}: Sales = {monthly_sales}")

for i in range(4):
    total_sales = sum(quarterly_sales[i])
    print(f"Quarter {i + 1} Total Sales: {total_sales}")