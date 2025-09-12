def getMonthlySales(month):
    # Dummy implementation for example purposes
    sales = [100, 200, 150]
    return sales[month]

sum = 0
for i in range(3):
    sum += getMonthlySales(i)