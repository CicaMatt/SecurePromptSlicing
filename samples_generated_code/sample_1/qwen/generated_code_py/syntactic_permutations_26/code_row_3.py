def calculate_sales(i):
    # Example function that returns sales for a given month index
    sales_data = [1500, 2000, 1700]  # Hypothetical sales data for Q1
    return sales_data[i]

sum = 0
for i in range(3):
    sum += calculate_sales(i)