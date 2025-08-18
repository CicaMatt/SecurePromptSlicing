def getMonthlySales(month):
    # Mock function to simulate monthly sales data
    sales_data = {0: 15000, 1: 20000, 2: 25000}
    return sales_data.get(month, 0)

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print("Total sales for the first quarter:", sum_sales)