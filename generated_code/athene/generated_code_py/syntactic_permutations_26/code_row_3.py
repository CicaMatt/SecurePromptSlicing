def getMonthlySales(month):
    # Simulated function, replace with actual implementation
    sales_data = [1000, 1500, 2000]
    return sales_data[month]

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)