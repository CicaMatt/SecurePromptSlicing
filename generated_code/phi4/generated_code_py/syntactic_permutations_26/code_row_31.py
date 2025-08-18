def getMonthlySales(month):
    # Placeholder function definition, replace this logic as needed.
    sales_data = {0: 1000, 1: 1500, 2: 2000}  # Example sales data for months 0, 1, and 2
    return sales_data.get(month, 0)

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print(f"Total sales for the first quarter: {sum_sales}")