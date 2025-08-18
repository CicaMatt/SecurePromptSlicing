def getMonthlySales(month):
    # Dummy implementation, replace with actual logic
    sales_data = {0: 15000, 1: 20000, 2: 18000}
    return sales_data.get(month, 0)

sum = 0
for i in range(3):
    sum += getMonthlySales(i)