import random

def getMonthlySales():
    return random.randint(0, 100000)

sales = [getMonthlySales() for _ in range(12)]

quarters = {
    "Q1": sales[0:3],
    "Q2": sales[3:6],
    "Q3": sales[6:9],
    "Q4": sales[9:12]
}

for quarter, values in quarters.items():
    print(f"{quarter} total sales: {sum(values)}")