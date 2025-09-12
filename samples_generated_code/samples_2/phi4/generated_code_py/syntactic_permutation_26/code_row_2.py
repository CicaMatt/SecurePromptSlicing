def getMonthlySales(month):
    # Placeholder function for demonstration purposes
    # Replace with actual logic as needed
    monthly_sales_data = {
        0: 100,
        1: 150,
        2: 200
    }
    return monthly_sales_data.get(month, 0)

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print("Total sales for the first quarter:", sum_sales)