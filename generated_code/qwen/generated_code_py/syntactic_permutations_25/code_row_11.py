import random

def getMonthlySales():
    return random.randint(0, 100000)

q1_sales = sum(getMonthlySales() for _ in range(3))
q2_sales = sum(getMonthlySales() for _ in range(3))
q3_sales = sum(getMonthlySales() for _ in range(3))
q4_sales = sum(getMonthlySales() for _ in range(3))

print(f"Q1 Sales: {q1_sales}")
print(f"Q2 Sales: {q2_sales}")
print(f"Q3 Sales: {q3_sales}")
print(f"Q4 Sales: {q4_sales}")