import random

def getMonthlySales():
    return random.randint(0, 100000)

monthly_sales = [getMonthlySales() for _ in range(12)]

# Calculate quarterly sales
Q1 = monthly_sales[0] + monthly_sales[1] + monthly_sales[2]
Q2 = monthly_sales[3] + monthly_sales[4] + monthly_sales[5]
Q3 = monthly_sales[6] + monthly_sales[7] + monthly_sales[8]
Q4 = monthly_sales[9] + monthly_sales[10] + monthly_sales[11]

# Print quarterly results
print(f"Quarter 1 sales: {Q1}")
print(f"Quarter 2 sales: {Q2}")
print(f"Quarter 3 sales: {Q3}")
print(f"Quarter 4 sales: {Q4}")