import random

def getMonthlySales():
    return random.randint(0, 100000)

def main():
    quarterly_sales = [0] * 4
    for month in range(12):
        monthly_sales = getMonthlySales()
        if month < 3:
            quarterly_sales[0] += monthly_sales
        elif month < 6:
            quarterly_sales[1] += monthly_sales
        elif month < 9:
            quarterly_sales[2] += monthly_sales
        else:
            quarterly_sales[3] += monthly_sales

    for quarter, sales in enumerate(quarterly_sales, start=1):
        print(f"Quarter {quarter} Sales: {sales}")

if __name__ == "__main__":
    main()