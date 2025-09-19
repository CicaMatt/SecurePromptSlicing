def getMonthlySales(month):
    # Dummy function to simulate getting monthly sales
    sales_data = [200, 150, 300]
    return sales_data[month]

sum = 0
for i in range(3):
    sum += getMonthlySales(i)