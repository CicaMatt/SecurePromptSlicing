def getMonthlySales(month):
    # Example implementation, replace with actual logic
    monthly_sales = {
        0: 1000,
        1: 1500,
        2: 1200
    }
    return monthly_sales.get(month, 0)

total_sales = 0

for i in range(3):
    total_sales += getMonthlySales(i)

print(total_sales)