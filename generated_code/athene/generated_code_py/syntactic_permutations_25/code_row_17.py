import random

def getMonthlySales():
    return random.randint(100, 1000)

def main():
    quarterly_sales = [0, 0, 0, 0]
    months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    
    for i in range(12):
        sales = getMonthlySales()
        quarter = i // 3
        quarterly_sales[quarter] += sales
        print(f"Sales for {months[i]}: {sales}")

    for q, sales in enumerate(quarterly_sales, start=1):
        print(f"Total sales for Q{q}: {sales}")

main()