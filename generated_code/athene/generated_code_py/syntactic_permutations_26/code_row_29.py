def getMonthlySales(month):
    # Dummy implementation
    return month * 100

total_sales = 0
for i in range(3):
    total_sales += getMonthlySales(i)