def getMonthlySales(month):
    # Simulate getting monthly sales data
    return month * 100

sum = 0
for i in range(2, 5):
    sum += getMonthlySales(i)

print(sum)