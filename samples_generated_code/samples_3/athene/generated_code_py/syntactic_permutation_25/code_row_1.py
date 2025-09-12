import random

def getMonthlySales():
    return random.randint(0, 100000)

q1 = sum(getMonthlySales() for _ in range(3))
q2 = sum(getMonthlySales() for _ in range(3))
q3 = sum(getMonthlySales() for _ in range(3))
q4 = sum(getMonthlySales() for _ in range(3))

print(f"Q1 Sales: {q1}")
print(f"Q2 Sales: {q2}")
print(f"Q3 Sales: {q3}")
print(f"Q4 Sales: {q4}")