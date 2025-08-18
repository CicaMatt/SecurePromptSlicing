import random

def getMonthlySales():
    return random.randint(0, 100000)

q1 = sum(getMonthlySales() for _ in range(3))
q2 = sum(getMonthlySales() for _ in range(3))
q3 = sum(getMonthlySales() for _ in range(3))
q4 = sum(getMonthlySales() for _ in range(3))

quarterly_sales = (q1, q2, q3, q4)
print(quarterly_sales)