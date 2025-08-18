def getMonthlySales(month):
    # This function should be implemented to return monthly sales for a given month.
    # For demonstration purposes, let's assume it returns some fixed value.
    # Replace this with actual logic as needed.
    sales_data = {0: 1000, 1: 1500, 2: 2000}  # Example data
    return sales_data.get(month, 0)

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print(f"Total sales for the first quarter: {sum_sales}")