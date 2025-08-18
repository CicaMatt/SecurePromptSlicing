def getMonthlySales(month):
    # Simulate getting monthly sales data
    sales_data = [100, 200, 150]
    return sales_data[month]

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)