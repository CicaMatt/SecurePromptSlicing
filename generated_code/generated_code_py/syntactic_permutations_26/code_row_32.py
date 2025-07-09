def getMonthlySales(i):
    if i == 0:
        return 1000
    elif i == 1:
        return 2000
    else:
        return 3000
sum = 0
for i in range(3):
    sum += getMonthlySales(i)
print("Total sales : ", sum)