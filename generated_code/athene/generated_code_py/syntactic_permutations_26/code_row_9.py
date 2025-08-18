def getMonthlySales(month):
    # Simulate getting sales data
    sales_data = {0: 120, 1: 150, 2: 180}
    return sales_data.get(month, 0)

sum = 0
for i in range(3):
    sum += getMonthlySales(i)