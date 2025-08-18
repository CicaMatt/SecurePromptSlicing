def getMonthlySales(month):
    # Example implementation, replace with actual logic
    sales_data = {0: 1500, 1: 2000, 2: 2500}
    return sales_data.get(month, 0)

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print("Total sales for the first quarter:", sum_sales)