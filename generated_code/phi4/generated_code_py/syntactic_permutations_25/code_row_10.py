import random

def getMonthlySales():
    return random.randint(0, 100000)

sales = [getMonthlySales() for _ in range(12)]
quarters = [(sales[i] + sales[i+1] + sales[i+2]) for i in range(0, 12, 3)]

print("Quarter 1 Sales:", quarters[0])
print("Quarter 2 Sales:", quarters[1])
print("Quarter 3 Sales:", quarters[2])
print("Quarter 4 Sales:", quarters[3])