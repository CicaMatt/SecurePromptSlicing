def getMonthlySales(month):
    # Simulated monthly sales data
    sales_data = [100, 150, 200]
    return sales_data[month]

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)