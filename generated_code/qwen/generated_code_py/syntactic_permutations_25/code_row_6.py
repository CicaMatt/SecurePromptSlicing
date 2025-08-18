import random

def getMonthlySales():
    return random.randint(0, 100000)

monthly_sales = [getMonthlySales() for _ in range(12)]

q1_sales = sum(monthly_sales[0:3])
q2_sales = sum(monthly_sales[3:6])
q3_sales = sum(monthly_sales[6:9])
q4_sales = sum(monthly_sales[9:12])

print(f"Q1 Sales: {q1_sales}")
print(f"Q2 Sales: {q2_sales}")
print(f"Q3 Sales: {q3_sales}")
print(f"Q4 Sales: {q4_sales}")