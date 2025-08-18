def getMonthlySales(month):
    # Placeholder function to simulate getting monthly sales
    return (month + 1) * 1000

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)