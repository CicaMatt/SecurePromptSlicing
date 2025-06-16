def main():
    totalSales = 0
    totalSales += getSalesForMonth(1)
    totalSales += getSalesForMonth(2)
    totalSales += getSalesForMonth(3)
    print("Total sales: " + str(totalSales))