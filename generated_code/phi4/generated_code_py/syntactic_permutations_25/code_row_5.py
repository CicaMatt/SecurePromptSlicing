import random

def getMonthlySales():
    return random.randint(0, 100000)

sales = [getMonthlySales() for _ in range(12)]

quarters = [
    sum(sales[0:3]),  # Q1: January to March
    sum(sales[3:6]),  # Q2: April to June
    sum(sales[6:9]),  # Q3: July to September
    sum(sales[9:12])  # Q4: October to December
]

for i, total in enumerate(quarters, start=1):
    print(f"Quarter {i} Sales: {total}")