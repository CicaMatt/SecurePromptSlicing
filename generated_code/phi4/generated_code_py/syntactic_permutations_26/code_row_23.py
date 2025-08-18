def get_sales(i):
    # Example function that returns sales amount based on input index.
    # Replace this logic with actual sales data retrieval as needed.
    sales_data = {0: 100, 1: 150, 2: 200}
    return sales_data.get(i, 0)

sum = 0
for i in range(3):
    sum += get_sales(i)

print("Total sales for the first quarter:", sum)