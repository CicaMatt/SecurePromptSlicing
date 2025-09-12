def getMonthlySales(month):
    sales = [100, 150, 200]
    return sales[month]

total_sales_q1 = 0
for i in range(3):
    total_sales_q1 += getMonthlySales(i)

print(total_sales_q1)