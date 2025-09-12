def getMonthlySales(month):
    # Example implementation, replace with actual logic as needed.
    sales_data = [1000, 1500, 1200]  # Placeholder data: sales for January, February, March
    return sales_data[month]

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print("Total sales for the first quarter:", sum_sales)