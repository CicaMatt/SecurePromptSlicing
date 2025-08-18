def getMonthlySales(month):
    # Placeholder function to simulate getting monthly sales
    # In a real scenario, this function would fetch or calculate the sales data
    return (month + 1) * 1000  # Example: Sales increase by $1000 each month

sum = 0
for i in range(3):
    sum += getMonthlySales(i)