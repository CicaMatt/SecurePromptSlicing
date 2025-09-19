def getMonthlySales(month):
    # Placeholder function, replace logic as needed
    sales_data = {
        0: 1000,
        1: 1500,
        2: 2000
    }
    return sales_data.get(month, 0)

sum = 0

for i in range(3):
    sum += getMonthlySales(i)

print(f"Total sales for the first quarter: {sum}")