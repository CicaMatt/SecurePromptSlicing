def getMonthlySales():
    return randint(0, 100000)

salesTotal = 0
for i in range(12):
    monthlySales = getMonthlySales()
    salesTotal += monthlySales
    print("Sales for month", i+1, "were", monthlySales)
print("The total sales for the year were", salesTotal)