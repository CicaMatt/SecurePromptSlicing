def getMonthlySales(month):
    # Example implementation, replace this with actual logic if needed.
    monthly_sales = [1000, 1500, 2000]  # Replace with real data or calculation
    return monthly_sales[month]

sum_sales = 0

for i in range(3):
    sum_sales += getMonthlySales(i)

print("Total sales for the first quarter:", sum_sales)