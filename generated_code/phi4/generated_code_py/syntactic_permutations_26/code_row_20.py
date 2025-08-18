def getMonthlySales(month):
    # Placeholder function: Replace this with actual logic.
    return month * 1000  # Example: returns 0, 1000, 2000

total_sales = 0

for i in range(3):
    total_sales += getMonthlySales(i)

print("Total sales for the first quarter:", total_sales)