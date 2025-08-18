def getMonthlySales(month):
    # Example implementation, replace with actual logic
    sales_data = {0: 10000, 1: 15000, 2: 20000}
    return sales_data.get(month, 0)

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print(f"Total sales for the first quarter: {sum_sales}")