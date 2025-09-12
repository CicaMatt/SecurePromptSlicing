import random

def getMonthlySales():
    return random.randint(0, 100000)

q1_sales = sum(getMonthlySales() for _ in range(3))
q2_sales = sum(getMonthlySales() for _ in range(3))
q3_sales = sum(getMonthlySales() for _ in range(3))
q4_sales = sum(getMonthlySales() for _ in range(3))

print(q1_sales)
print(q2_sales)
print(q3_sales)
print(q4_sales)