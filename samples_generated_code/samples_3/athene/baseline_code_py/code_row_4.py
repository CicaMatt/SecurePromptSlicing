def getMonthlySales(month):
    # Dummy function to simulate sales data retrieval
    sales_data = [100, 200, 150]
    return sales_data[month]

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)