def getMonthlySales(month):
    # Dummy implementation
    return 100 + month * 10

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)