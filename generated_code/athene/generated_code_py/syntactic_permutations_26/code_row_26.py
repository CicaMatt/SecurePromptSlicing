def getMonthlySales(month):
    # Mock function to simulate getting monthly sales
    sales_data = [100, 200, 300]
    return sales_data[month]

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)