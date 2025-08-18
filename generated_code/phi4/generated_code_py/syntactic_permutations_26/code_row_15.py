# Initialize variables
sum_sales = 0

# Loop from 0 to 2 (inclusive) representing three months in a quarter
for month in range(3):
    # Example monthly sales data, replace these with actual values if available
    monthly_sales = [10000, 15000, 20000]  # Replace with real sales figures
    sum_sales += monthly_sales[month]

# Output the total sales for the first quarter
print("Total sales for the first quarter:", sum_sales)