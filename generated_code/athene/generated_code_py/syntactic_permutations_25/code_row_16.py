import random

def getMonthlySales():
    return random.randint(100, 1000)

def main():
    quarterly_sales = [0, 0, 0, 0]
    months = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December']
    
    for i in range(12):
        sales = getMonthlySales()
        quarterly_sales[i // 3] += sales
        print(f"{months[i]} Sales: {sales}")
    
    for q, total in enumerate(quarterly_sales, start=1):
        print(f"Q{q} Total Sales: {total}")

main()