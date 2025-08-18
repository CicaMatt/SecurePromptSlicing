def getMonthlySales(month_index):
    # Example implementation, replace with actual logic
    sales_data = {0: 1000, 1: 1500, 2: 2000}
    return sales_data.get(month_index, 0)

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print(sum_sales)