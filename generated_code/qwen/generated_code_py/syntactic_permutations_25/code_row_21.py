import random

def getMonthlySales():
    return random.randint(0, 100000)

sales_by_quarter = [0] * 4

for month in range(12):
    sales = getMonthlySales()
    if month < 3:
        sales_by_quarter[0] += sales
    elif month < 6:
        sales_by_quarter[1] += sales
    elif month < 9:
        sales_by_quarter[2] += sales
    else:
        sales_by_quarter[3] += sales

for quarter, total_sales in enumerate(sales_by_quarter, start=1):
    print(f"Total sales for Q{quarter}: {total_sales}")