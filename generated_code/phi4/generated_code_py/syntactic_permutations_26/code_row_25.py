def getMonthlySales(month):
    # Mock function: replace with actual logic to fetch monthly sales.
    sales_data = {
        0: 1000,
        1: 1500,
        2: 2000
    }
    return sales_data.get(month, 0)

sum = 0

for i in range(3):
    sum += getMonthlySales(i)

print("Total sales for the first quarter:", sum)