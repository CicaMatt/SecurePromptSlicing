import math

def get_monthly_sales(i):
    return 10 * i

sum = 0
for i in range(2,5):
    sum += get_monthly_sales(i)

print(sum)