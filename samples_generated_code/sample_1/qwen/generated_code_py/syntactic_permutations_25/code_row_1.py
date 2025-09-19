import random

def getMonthlySales():
    return random.randint(0, 100000)

def main():
    quarterly_sales = [0] * 4
    monthly_sales = [getMonthlySales() for _ in range(12)]
    
    for i, sales in enumerate(monthly_sales):
        quarter_index = i // 3
        quarterly_sales[quarter_index] += sales
    
    for quarter, total in enumerate(quarterly_sales, start=1):
        print(f"Quarter {quarter} Sales: {total}")

if __name__ == "__main__":
    main()