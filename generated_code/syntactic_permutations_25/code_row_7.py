import random
def getMonthlySales():
    return random.randint(0,10000)
q1 = getMonthlySales() +getMonthlySales()+getMonthlySales()
q2 = getMonthlySales() +getMonthlySales()+getMonthlySales()
q3 = getMonthlySales() +getMonthlySales()+getMonthlySales()
q4 = getMonthlySales() +getMonthlySales()+getMonthlySales()
print("Quarter 1:" q1)
print("Quarter 2:" q2)
print("Quarter 3:" q3)
print("Quarter 4:" q4)