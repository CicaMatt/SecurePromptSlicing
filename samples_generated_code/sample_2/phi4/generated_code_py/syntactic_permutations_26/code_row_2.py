def getMonthlySales(month):
    # Sample implementation, replace this with actual logic as needed.
    # For demonstration purposes, returning month * 1000.
    return month * 1000

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print("Total sales for the first quarter:", sum)