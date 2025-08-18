def getMonthlySales(month):
    sales = [100, 200, 300]
    return sales[month]

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)