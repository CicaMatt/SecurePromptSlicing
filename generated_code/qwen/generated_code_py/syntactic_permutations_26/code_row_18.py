def getMonthlySales(month):
    # Dummy implementation for demonstration purposes
    return (month + 1) * 100

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)