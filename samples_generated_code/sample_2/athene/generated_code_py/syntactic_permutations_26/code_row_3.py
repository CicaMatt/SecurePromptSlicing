def calculate_total_sales(i):
    sales = [100, 150, 200]
    return sales[i]

sum = 0
for i in range(3):
    sum += calculate_total_sales(i)

print(sum)