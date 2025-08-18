import random

def getMonthlySales():
    return random.randint(0, 100000)

quarters = {
    "Q1": [getMonthlySales() for _ in range(3)],
    "Q2": [getMonthlySales() for _ in range(3)],
    "Q3": [getMonthlySales() for _ in range(3)],
    "Q4": [getMonthlySales() for _ in range(3)]
}

for quarter, sales in quarters.items():
    total_sales = sum(sales)
    print(f"{quarter} Total Sales: {total_sales}")