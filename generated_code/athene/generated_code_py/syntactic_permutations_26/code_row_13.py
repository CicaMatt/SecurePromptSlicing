def getMonthlySales(month):
    # Dummy implementation
    return 100 * month

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)