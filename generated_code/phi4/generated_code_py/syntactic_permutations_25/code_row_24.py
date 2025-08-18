import random

def getMonthlySales():
    return random.randint(0, 100000)

quarterly_sales = [0] * 4

for month in range(1, 13):
    monthly_sales = getMonthlySales()
    
    if month == 1 or month == 2 or month == 3:
        quarterly_sales[0] += monthly_sales
    elif month == 4 or month == 5 or month == 6:
        quarterly_sales[1] += monthly_sales
    elif month == 7 or month == 8 or month == 9:
        quarterly_sales[2] += monthly_sales
    else:
        quarterly_sales[3] += monthly_sales

print("Quarterly Sales:", quarterly_sales)