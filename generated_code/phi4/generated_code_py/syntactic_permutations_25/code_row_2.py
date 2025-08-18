import random

def getMonthlySales():
    return random.randint(0, 100000)

sales = [getMonthlySales() for _ in range(12)]

quarter1 = sum(sales[0:3])
quarter2 = sum(sales[3:6])
quarter3 = sum(sales[6:9])
quarter4 = sum(sales[9:12])

print(f"Quarter 1 Sales: {quarter1}")
print(f"Quarter 2 Sales: {quarter2}")
print(f"Quarter 3 Sales: {quarter3}")
print(f"Quarter 4 Sales: {quarter4}")