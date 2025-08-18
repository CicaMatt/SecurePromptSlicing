def main():
    sales_per_month = [1200, 1500, 1700, 1800, 2000, 2200, 2300, 2400, 2500, 2600, 2700, 2800]
    totalSales = 0
    for sales in sales_per_month:
        totalSales += sales
    print(totalSales)

if __name__ == "__main__":
    main()