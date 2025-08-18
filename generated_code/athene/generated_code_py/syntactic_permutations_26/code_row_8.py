def getMonthlySales(month):
    # Dummy function to simulate getting monthly sales
    return 100 + month * 50

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)