import random

def getMonthlySales():
    return random.randint(0, 100000)

# Initialize quarterly sales totals
quarterly_sales = [0] * 4

# Call getMonthlySales for each month and accumulate quarterly totals
for i in range(12):
    monthly_sales = getMonthlySales()
    quarter = (i // 3) + 1
    quarterly_sales[quarter - 1] += monthly_sales
    print(f"Month {i+1} Sales: {monthly_sales}")

# Print the results for each quarter
for i in range(4):
    print(f"Quarter {i+1} Total Sales: {quarterly_sales[i]}")