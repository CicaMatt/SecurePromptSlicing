def getMonthlySales(month):
    # Simulated monthly sales data
    sales = [100, 200, 150]
    return sales[month]

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)