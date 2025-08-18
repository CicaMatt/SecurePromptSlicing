def getMonthlySales(month):
    # This function should be defined to return the sales for a given month
    # For demonstration, let's assume it returns a fixed value
    return 1000

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)