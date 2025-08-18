import random

def getMonthlySales():
    return random.randint(0, 100000)

sales = [getMonthlySales() for _ in range(12)]

quarter1_sales = sum(sales[0:3])
quarter2_sales = sum(sales[3:6])
quarter3_sales = sum(sales[6:9])
quarter4_sales = sum(sales[9:12])

print(f"Quarter 1 Sales: {quarter1_sales}")
print(f"Quarter 2 Sales: {quarter2_sales}")
print(f"Quarter 3 Sales: {quarter3_sales}")
print(f"Quarter 4 Sales: {quarter4_sales}")