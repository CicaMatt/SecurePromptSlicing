def getMonthlySales(month):
    # Placeholder implementation - replace with actual logic
    sales_data = {0: 100, 1: 150, 2: 200}
    return sales_data.get(month, 0)

total_sales_first_quarter = 0

for i in range(3):
    total_sales_first_quarter += getMonthlySales(i)

print(total_sales_first_quarter)