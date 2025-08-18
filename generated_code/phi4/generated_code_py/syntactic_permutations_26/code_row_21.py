def getMonthlySales(month):
    # Example implementation, replace this with actual logic.
    sales_data = {0: 1000, 1: 1500, 2: 2000}
    return sales_data.get(month, 0)

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print("Total sales for the first quarter:", sum_sales)