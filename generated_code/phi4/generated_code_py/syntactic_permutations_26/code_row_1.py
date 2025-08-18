def getMonthlySales(month):
    # Dummy implementation, replace it as necessary.
    monthly_sales = [1000, 1500, 2000]  # Example values for months 0, 1, and 2
    return monthly_sales[month]

sum = 0

for i in range(3):  # Iterates from 0 to 2 inclusive
    sum += getMonthlySales(i)

print("Total sales for the first quarter:", sum)