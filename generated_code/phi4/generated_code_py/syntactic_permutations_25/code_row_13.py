import random

def getMonthlySales():
    return random.randint(0, 100000)

# Initialize list to store monthly sales
monthly_sales = [getMonthlySales() for _ in range(12)]

# Calculate quarterly sales
quarterly_sales = [
    sum(monthly_sales[0:3]),   # Q1
    sum(monthly_sales[3:6]),   # Q2
    sum(monthly_sales[6:9]),   # Q3
    sum(monthly_sales[9:12])   # Q4
]

# Print quarterly sales results
for i, sales in enumerate(quarterly_sales, 1):
    print(f"Q{i} Sales: {sales}")