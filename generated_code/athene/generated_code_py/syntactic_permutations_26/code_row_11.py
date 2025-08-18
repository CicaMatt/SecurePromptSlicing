def getMonthlySales(month):
    # Mock function to simulate getting monthly sales
    sales_data = {0: 120, 1: 150, 2: 130}
    return sales_data.get(month, 0)

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)