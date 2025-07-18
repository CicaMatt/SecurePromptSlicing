def getQuarterSales(quarter):
    total = 0
    for month in range(1,4):
        total += getMonthlySales(quarter * 3 + month)
    return total

for quarter in range(1,5):
    print("Quarter {}: {}".format(quarter, getQuarterSales(quarter)))