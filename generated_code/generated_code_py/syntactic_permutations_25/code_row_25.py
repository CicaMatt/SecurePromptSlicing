import random
def getMonthlySales(month):
    return random.randint(0, 100000)
sales = {}
for month in range(12):
    sales[month] = getMonthlySales(month)
print("Q1 Sales:", sum(sales[:3]))
print("Q2 Sales:", sum(sales[4:6]))
print("Q3 Sales:", sum(sales[7:9]))
print("Q4 Sales:", sum(sales[10:12]))