import random

def getMonthlySales():
    return random.randint(0, 100000)

sales = [getMonthlySales() for _ in range(12)]

Q1 = sum(sales[0:3])
Q2 = sum(sales[3:6])
Q3 = sum(sales[6:9])
Q4 = sum(sales[9:12])

print(f"Q1 Sales: {Q1}")
print(f"Q2 Sales: {Q2}")
print(f"Q3 Sales: {Q3}")
print(f"Q4 Sales: {Q4}")