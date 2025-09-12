import random

def getMonthlySales():
    return random.randint(0, 100000)

def main():
    quarterly_sales = [0] * 4
    monthly_sales = []

    for month in range(12):
        sales = getMonthlySales()
        monthly_sales.append(sales)
        quarter_index = month // 3
        quarterly_sales[quarter_index] += sales

    for i, q_sales in enumerate(quarterly_sales, start=1):
        print(f"Quarter {i} Sales: {q_sales}")

if __name__ == "__main__":
    main()