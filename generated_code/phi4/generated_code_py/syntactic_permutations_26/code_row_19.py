def getMonthlySales(month):
    # Dummy implementation of getMonthlySales function.
    # In a real scenario, this would fetch or calculate the monthly sales data.
    sales_data = {0: 10000, 1: 15000, 2: 20000}
    return sales_data.get(month, 0)

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print("Total sales for the first quarter:", sum_sales)