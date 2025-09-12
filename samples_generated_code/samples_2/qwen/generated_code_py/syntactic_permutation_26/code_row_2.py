def getMonthlySales(month):
    # Placeholder function to simulate getting monthly sales
    # Replace this with actual logic to retrieve sales data
    sales_data = [1500, 2000, 2500]  # Example sales data for months 0, 1, and 2
    return sales_data[month]

sum = 0
for i in range(3):
    sum += getMonthlySales(i)