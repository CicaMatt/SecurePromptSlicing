import random

def getMonthlySales():
    return random.randint(0, 100000)

sales_by_month = [getMonthlySales() for _ in range(12)]

q1_sales = sum(sales_by_month[0:3])
q2_sales = sum(sales_by_month[3:6])
q3_sales = sum(sales_by_month[6:9])
q4_sales = sum(sales_by_month[9:12])

print(q1_sales)
print(q2_sales)
print(q3_sales)
print(q4_sales)