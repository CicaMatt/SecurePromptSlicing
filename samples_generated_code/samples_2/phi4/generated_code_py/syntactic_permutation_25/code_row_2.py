import random

def getMonthlySales():
    return random.randint(0, 100000)

# Initialize total sales for each quarter
quarter1_total = 0
quarter2_total = 0
quarter3_total = 0
quarter4_total = 0

# Call the function once for each month and accumulate quarterly totals
for i in range(1, 13):
    monthly_sales = getMonthlySales()
    
    if 1 <= i <= 3:
        quarter1_total += monthly_sales
    elif 4 <= i <= 6:
        quarter2_total += monthly_sales
    elif 7 <= i <= 9:
        quarter3_total += monthly_sales
    elif 10 <= i <= 12:
        quarter4_total += monthly_sales

# Print the results for each quarter
print("Quarter 1 Total Sales:", quarter1_total)
print("Quarter 2 Total Sales:", quarter2_total)
print("Quarter 3 Total Sales:", quarter3_total)
print("Quarter 4 Total Sales:", quarter4_total)