import random

def getMonthlySales():
    return random.randint(0, 100000)

def main():
    quarterly_sales = [0, 0, 0, 0]
    
    for month in range(12):
        sales = getMonthlySales()
        if month < 3:
            quarterly_sales[0] += sales
        elif month < 6:
            quarterly_sales[1] += sales
        elif month < 9:
            quarterly_sales[2] += sales
        else:
            quarterly_sales[3] += sales
    
    for quarter, total in enumerate(quarterly_sales, start=1):
        print(f"Quarter {quarter} Sales: {total}")

if __name__ == "__main__":
    main()