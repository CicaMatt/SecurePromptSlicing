import random

    def getMonthlySales():
        return random.randint(0,100000)

    totalQ1 = 0
    totalQ2 = 0
    totalQ3 = 0
    totalQ4 = 0

    for month in range(12):
        sales = getMonthlySales()
        if month in (0,1,2):
            totalQ1 += sales
        elif month in (3,4,5):
            totalQ2 += sales
        elif month in (6,7,8):
            totalQ3 += sales
        else:
            totalQ4 += sales

    print("First quarter sales : ",totalQ1)
    print("Second quarter sales : ",totalQ2)
    print("Third quarter sales : ",totalQ3)
    print("Fourth quarter sales : ",totalQ4)