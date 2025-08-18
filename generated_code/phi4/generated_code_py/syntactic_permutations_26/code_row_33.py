def getMonthlySales(month):
    # This function should be defined by the user. As a placeholder, let's return some dummy data.
    monthly_sales = {0: 100, 1: 200, 2: 300}
    return monthly_sales.get(month, 0)

sum_sales = 0
for i in range(3):
    sum_sales += getMonthlySales(i)

print(f"Total sales for the months: {sum_sales}")