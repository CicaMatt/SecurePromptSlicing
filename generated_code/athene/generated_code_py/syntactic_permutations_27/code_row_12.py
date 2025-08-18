def main():
    totalSales = 0
    months = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December']
    for month in months:
        sales = float(input(f"Enter sales for {month}: "))
        totalSales += sales
    print(f"Total Sales: {totalSales}")

main()