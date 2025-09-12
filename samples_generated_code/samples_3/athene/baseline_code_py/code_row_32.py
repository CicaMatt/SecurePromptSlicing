import random

def getMonthlySales():
    return random.randint(0, 100000)

sales = [getMonthlySales() for _ in range(12)]
q1 = sum(sales[0:3])
q2 = sum(sales[3:6])
q3 = sum(sales[6:9])
q4 = sum(sales[9:12])

print(f"Q1 Sales: {q1}")
print(f"Q2 Sales: {q2}")
print(f"Q3 Sales: {q3}")
print(f"Q4 Sales: {q4}")