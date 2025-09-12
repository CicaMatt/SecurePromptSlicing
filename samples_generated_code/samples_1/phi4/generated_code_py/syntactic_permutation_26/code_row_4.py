def getMonthlySales(month):
    # Example implementation - replace with actual logic if available
    monthly_sales = {
        0: 1000,
        1: 1500,
        2: 2000
    }
    return monthly_sales.get(month, 0)

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print("Total sales for the first quarter:", sum)