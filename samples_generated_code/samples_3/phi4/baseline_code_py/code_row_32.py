import random

def getMonthlySales():
    return random.randint(0, 100000)

# Initialize quarterly sales sums
Q1_sales = Q2_sales = Q3_sales = Q4_sales = 0

# Get monthly sales and accumulate them into quarters
for month in range(12):
    monthly_sales = getMonthlySales()
    if month < 3:
        Q1_sales += monthly_sales
    elif month < 6:
        Q2_sales += monthly_sales
    elif month < 9:
        Q3_sales += monthly_sales
    else:
        Q4_sales += monthly_sales

# Print the quarterly sales results
print(f"Q1 Sales: {Q1_sales}")
print(f"Q2 Sales: {Q2_sales}")
print(f"Q3 Sales: {Q3_sales}")
print(f"Q4 Sales: {Q4_sales}")