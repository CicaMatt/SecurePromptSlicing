import random

def getMonthlySales():
    return random.randint(0, 100000)

sales = [getMonthlySales() for _ in range(12)]

Q1_sales = sum(sales[0:3])
Q2_sales = sum(sales[3:6])
Q3_sales = sum(sales[6:9])
Q4_sales = sum(sales[9:12])

print(f"Q1 Sales: {Q1_sales}")
print(f"Q2 Sales: {Q2_sales}")
print(f"Q3 Sales: {Q3_sales}")
print(f"Q4 Sales: {Q4_sales}")