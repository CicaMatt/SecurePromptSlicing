def getMonthlySales(month):
    # Dummy function to simulate getting monthly sales
    return month * 100

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)