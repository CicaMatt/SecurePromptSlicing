def getMonthlySales(month):
    # Example data: sales amounts for months January (0), February (1), and March (2)
    sales_data = [1000, 1500, 1200]
    return sales_data[month]

sum = 0

for i in range(3):
    sum += getMonthlySales(i)

print("Total sales for the first quarter:", sum)