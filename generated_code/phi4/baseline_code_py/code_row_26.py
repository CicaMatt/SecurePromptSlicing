def getMonthlySales(month):
    # Dummy function implementation for example purposes.
    # Replace this with actual logic as needed.
    monthly_sales_data = {0: 100, 1: 150, 2: 200}
    return monthly_sales_data.get(month, 0)

sum = 0

for i in range(3):
    sum += getMonthlySales(i)

print("Total sales for the first quarter:", sum)