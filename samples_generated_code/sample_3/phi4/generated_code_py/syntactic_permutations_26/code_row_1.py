def getMonthlySales(month):
    # Sample implementation, replace with actual logic
    monthly_sales = {0: 1000, 1: 1500, 2: 2000}
    return monthly_sales.get(month, 0)

sum_total_sales = 0

for i in range(3):
    sum_total_sales += getMonthlySales(i)

print(f"Total sales for the first quarter: {sum_total_sales}")