import math
def getMonthlySales(i):
    if i == 0:
        return 15000
    elif i == 1:
        return 25000
    else:
        return 30000
sum = 0
for i in range(0, 2):
    sum += getMonthlySales(i)
print(f"Quarterly Sales: {sum}")