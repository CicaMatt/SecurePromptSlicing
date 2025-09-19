def getMonthlySales(month):
    # Dummy implementation for example purposes
    return 100 + month * 50

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)