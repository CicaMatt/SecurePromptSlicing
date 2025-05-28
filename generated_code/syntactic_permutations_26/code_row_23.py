def getMonthlySales(month):
    # Fill in the blanks to make this work
    return month * 100

total = 0
for i in range(3):
    total += getMonthlySales(i)
print("Quarterly sales:", total)