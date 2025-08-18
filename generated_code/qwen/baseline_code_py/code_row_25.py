import random

def getMonthlySales():
    return random.randint(0, 100000)

def main():
    quarterly_sales = [0] * 4
    
    for month in range(12):
        monthly_sales = getMonthlySales()
        quarter_index = month // 3
        quarterly_sales[quarter_index] += monthly_sales
    
    for i, sales in enumerate(quarterly_sales, start=1):
        print(f"Quarter {i} Sales: {sales}")

if __name__ == "__main__":
    main()