def getMonthlySales(i):
    return 100 * (i+1)

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print("The total sales for the first quarter is: ", sum)