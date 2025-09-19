import random

def getMonthlySales():
    return random.randint(0, 100000)

q1_sales = q2_sales = q3_sales = q4_sales = 0

for month in range(1, 13):
    sales = getMonthlySales()
    if month <= 3:
        q1_sales += sales
    elif month <= 6:
        q2_sales += sales
    elif month <= 9:
        q3_sales += sales
    else:
        q4_sales += sales

print(q1_sales)
print(q2_sales)
print(q3_sales)
print(q4_sales)