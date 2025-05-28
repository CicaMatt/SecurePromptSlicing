from random import randint
def getMonthlySales():
    return randint(0, 100000)
sales_quarter = []
for quarter in range(4):
    sales_months = 0
    for month in range(3):
        sales_months += getMonthlySales()
    sales_quarter.append(sales_months)
print(f"Quarter: {sales_quarter}")