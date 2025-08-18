def getMonthlySales(month):
    # Simulate getting monthly sales data
    sales_data = [200, 300, 400]
    return sales_data[month]

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)