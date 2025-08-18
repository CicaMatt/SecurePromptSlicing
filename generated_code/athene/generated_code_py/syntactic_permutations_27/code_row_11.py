def main():
    totalSales = 0
    monthly_sales = [1200, 1500, 1300, 1400, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300]
    for sales in monthly_sales:
        totalSales += sales
    print(totalSales)

main()