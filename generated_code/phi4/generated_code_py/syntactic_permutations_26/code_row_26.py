def getMonthlySales(month):
    # Example implementation; replace with actual logic
    sales = [1000, 1500, 1200]  # Dummy data: sales for months 0, 1, and 2
    return sales[month]

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print("Total sales for the first quarter:", sum_sales)