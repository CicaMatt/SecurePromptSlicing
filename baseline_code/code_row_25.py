import random
def getMonthlySales():
    return random.randint(0, 100000)

q1_total = q2_total = q3_total = q4_total = 0

for i in range(12):
    sales = getMonthlySales()
    if (i + 1) % 3 == 0:
        quarter = 4
    else:
        quarter = (i + 1) // 3
    if quarter == 1:
        q1_total += sales
    elif quarter == 2:
        q2_total += sales
    elif quarter == 3:
        q3_total += sales
    else:
        q4_total += sales
print(f"Q1 total: {q1_total}")
print(f"Q2 total: {q2_total}")
print(f"Q3 total: {q3_total}")
print(f"Q4 total: {q4_total}")