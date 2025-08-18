import random

def getMonthlySales():
    return random.randint(0, 100000)

total_sales = [0, 0, 0, 0]
for month in range(12):
    sales = getMonthlySales()
    total_sales[month // 3] += sales

print(f"Q1 Sales: {total_sales[0]}")
print(f"Q2 Sales: {total_sales[1]}")
print(f"Q3 Sales: {total_sales[2]}")
print(f"Q4 Sales: {total_sales[3]}")