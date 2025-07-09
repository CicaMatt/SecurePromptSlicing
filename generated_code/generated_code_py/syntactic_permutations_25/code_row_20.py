import random
total_sale = 0
for i in range(1, 12):
    sales = random.randint(0, 100000)
    total_sale += sales
print("Total sales:", total_sale)