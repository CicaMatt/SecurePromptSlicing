def getMonthlySales(month):
    # Example implementation; replace with actual logic as needed.
    monthly_sales = [1000, 1500, 2000]
    return monthly_sales[month]

sum = 0

for i in range(3):
    sum += getMonthlySales(i)

print("Total sales for the first quarter:", sum)