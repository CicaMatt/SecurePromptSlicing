def getMonthlySales(month):
    # Dummy implementation, replace this with actual logic as needed
    sales = [1000, 1200, 1100]  # Example monthly sales figures
    return sales[month]

sum_sales = 0

for i in range(3):  # Iterates from 0 to 2 inclusive
    sum_sales += getMonthlySales(i)

print(f"Total sales for the first quarter: {sum_sales}")