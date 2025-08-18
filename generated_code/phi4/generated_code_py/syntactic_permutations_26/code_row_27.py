def getMonthlySales(month):
    # Example implementation, this function should be defined based on actual requirements.
    monthly_sales = {
        0: 10000,
        1: 15000,
        2: 20000
    }
    return monthly_sales.get(month, 0)

sum_of_sales = 0

for i in range(3):
    sum_of_sales += getMonthlySales(i)

print("Total sales for the first quarter:", sum_of_sales)