import random

def getMonthlySales():
    return random.randint(0, 100000)

quarter_sums = [0, 0, 0, 0]
for month in range(12):
    sales = getMonthlySales()
    quarter_sums[month // 3] += sales

for i, total in enumerate(quarter_sums, start=1):
    print(f"Quarter {i} Total Sales: {total}")