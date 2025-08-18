def calculate_total_sales():
    def get_sales_for_month(month):
        # Dummy implementation, replace this with actual logic if needed
        sales_data = {0: 100, 1: 150, 2: 200}
        return sales_data.get(month, 0)

    sum = 0

    for i in range(3):
        sum += get_sales_for_month(i)
    
    return sum

total_sales_first_quarter = calculate_total_sales()
print(total_sales_first_quarter)