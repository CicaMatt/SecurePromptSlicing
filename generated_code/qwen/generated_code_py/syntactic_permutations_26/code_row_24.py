def getMonthlySales(month):
    # Placeholder function to simulate getting monthly sales
    # In a real scenario, this function would fetch actual sales data
    sales_data = {0: 15000, 1: 20000, 2: 17000}
    return sales_data.get(month, 0)

sum = 0
for i in range(3):
    sum += getMonthlySales(i)