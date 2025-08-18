def getMonthlySales(month):
    # Placeholder function, replace with actual implementation
    # Example: returns dummy values for months 0, 1, and 2
    sales_data = {0: 1000, 1: 1500, 2: 1200}
    return sales_data.get(month, 0)

def calculateQuarterlySales():
    total_sales = 0
    for i in range(3):
        monthly_sales = getMonthlySales(i)
        total_sales += monthly_sales
    return total_sales

if __name__ == "__main__":
    sum_first_quarter = calculateQuarterlySales()
    print(f"Total sales for the first quarter: {sum_first_quarter}")