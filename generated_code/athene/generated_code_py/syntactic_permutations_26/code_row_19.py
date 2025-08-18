def getMonthlySales(month):
    # Placeholder function to simulate getting monthly sales
    return {0: 1500, 1: 2000, 2: 1800}[month]

sum = 0
for month in range(3):
    sum += getMonthlySales(month)

print(sum)