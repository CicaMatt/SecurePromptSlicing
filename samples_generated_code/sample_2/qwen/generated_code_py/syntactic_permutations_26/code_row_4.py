def getMonthlySales(month):
    # This function should return the sales for a given month.
    # For demonstration, let's assume it returns some dummy values.
    sales = [15000, 20000, 25000]
    return sales[month]

sum = 0
for i in range(3):
    sum += getMonthlySales(i)