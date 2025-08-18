def getMonthlySales(month):
    # Dummy implementation for demonstration purposes.
    # Replace this function with the actual logic as needed.
    sales_data = {
        0: 100,
        1: 150,
        2: 200
    }
    return sales_data.get(month, 0)

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print(sum_sales)