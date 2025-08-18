def main():
    monthly_sales = [1200, 1500, 1800, 2100, 2400, 2700, 3000, 3300, 3600, 3900, 4200, 4500]
    totalSales = 0
    for sales in monthly_sales:
        totalSales += sales
    print(totalSales)

if __name__ == "__main__":
    main()