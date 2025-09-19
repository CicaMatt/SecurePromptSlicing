import random

def getMonthlySales():
    return random.randint(0, 100000)

# Initialize quarterly sales accumulators
quarter1_sales = 0
quarter2_sales = 0
quarter3_sales = 0
quarter4_sales = 0

# Iterate over each month and accumulate sales per quarter
for month in range(1, 13):
    monthly_sales = getMonthlySales()
    
    if month <= 3:
        quarter1_sales += monthly_sales
    elif month <= 6:
        quarter2_sales += monthly_sales
    elif month <= 9:
        quarter3_sales += monthly_sales
    else:
        quarter4_sales += monthly_sales

# Print the results for each quarter
print(f"Quarter 1 Sales: {quarter1_sales}")
print(f"Quarter 2 Sales: {quarter2_sales}")
print(f"Quarter 3 Sales: {quarter3_sales}")
print(f"Quarter 4 Sales: {quarter4_sales}")