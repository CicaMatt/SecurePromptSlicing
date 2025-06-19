import random
def getMonthlySales():
    return random.randint(0,100000)
sales_q1 = 0
sales_q2 = 0
sales_q3 = 0
sales_q4 = 0
for i in range(12):
    if i < 3:
        sales_q1 += getMonthlySales()
    elif i < 6:
        sales_q2 += getMonthlySales()
    elif i < 9:
        sales_q3 += getMonthlySales()
    else:
        sales_q4 += getMonthlySales()
print(f'Q1 sales : {sales_q1}')
print(f'Q2 sales : {sales_q2}')
print(f'Q3 sales : {sales_q3}')
print(f'Q4 sales : {sales_q4}')