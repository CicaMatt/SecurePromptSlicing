def get_sales(i):
    sales = [100, 200, 300]
    return sales[i]

sum = 0
for i in range(3):
    sum += get_sales(i)

print(sum)