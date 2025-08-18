def getMonthlySales(month):
    # Placeholder function, replace with actual implementation
    return (month + 1) * 1000

total_sales = 0
for i in range(3):
    total_sales += getMonthlySales(i)
print(total_sales)