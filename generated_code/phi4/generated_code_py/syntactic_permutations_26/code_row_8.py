def getMonthlySales(month):
    # Example implementation, replace with actual logic
    monthly_sales = {
        0: 10000,
        1: 15000,
        2: 20000
    }
    return monthly_sales.get(month, 0)

sum = 0

for i in range(3):  # Iterates from 0 to 2 inclusive
    sum += getMonthlySales(i)

print("Total sales for the first quarter:", sum)