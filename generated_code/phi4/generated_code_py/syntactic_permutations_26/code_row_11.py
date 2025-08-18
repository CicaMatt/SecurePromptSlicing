def getMonthlySales(month):
    # Dummy implementation, replace with actual logic if needed.
    monthly_sales_data = {0: 100, 1: 150, 2: 200}
    return monthly_sales_data.get(month, 0)

sum_sales = 0

for i in range(3):  # Iterating from 0 to 2
    sum_sales += getMonthlySales(i)

print(f"Total sales for the first quarter: {sum_sales}")