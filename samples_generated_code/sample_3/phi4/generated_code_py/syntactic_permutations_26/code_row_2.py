def getMonthlySales(month):
    # Placeholder function, replace with actual logic.
    monthly_sales = {
        0: 1000,
        1: 1500,
        2: 1200
    }
    return monthly_sales.get(month, 0)

sum = 0

for i in range(3):
    sum += getMonthlySales(i)

print(f"Total sales for the first quarter: {sum}")