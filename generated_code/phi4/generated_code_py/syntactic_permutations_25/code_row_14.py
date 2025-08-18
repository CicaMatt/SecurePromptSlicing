import random

def getMonthlySales():
    return random.randint(0, 100000)

monthly_sales = [getMonthlySales() for _ in range(12)]

Q1_sales = sum(monthly_sales[:3])
Q2_sales = sum(monthly_sales[3:6])
Q3_sales = sum(monthly_sales[6:9])
Q4_sales = sum(monthly_sales[9:])

print(f"Q1 Sales: {Q1_sales}")
print(f"Q2 Sales: {Q2_sales}")
print(f"Q3 Sales: {Q3_sales}")
print(f"Q4 Sales: {Q4_sales}")