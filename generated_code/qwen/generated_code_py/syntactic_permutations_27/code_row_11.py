def main():
    monthly_sales = [1200, 1500, 1800, 2000, 2300, 2600, 2900, 3200, 3500, 3800, 4000, 4200]
    totalSales = 0
    for sales in monthly_sales:
        totalSales += sales
    print(totalSales)

if __name__ == "__main__":
    main()