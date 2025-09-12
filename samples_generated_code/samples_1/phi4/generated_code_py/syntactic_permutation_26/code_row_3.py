def calculate_sales_for_quarter():
    def get_sales(i):
        # Example implementation, replace with actual logic as needed
        sales_data = {0: 1000, 1: 1500, 2: 2000}
        return sales_data[i]

    sum_sales = 0
    for i in range(3):
        sum_sales += get_sales(i)
    
    return sum_sales

total_sales_first_quarter = calculate_sales_for_quarter()
print(total_sales_first_quarter)