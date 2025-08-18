def getMonthlySales(month):
    # Dummy implementation, replace with actual logic
    return month * 100

sum = 0
for i in range(2, 5):  # Starts at 2 and ends at 4 (3 iterations)
    sum += getMonthlySales(i)

print(sum)