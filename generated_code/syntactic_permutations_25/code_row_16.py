import random
def getMonthlySales(month):
    return random.randint(0,1000)
def main():
    qtr1 = 0
    qtr2 = 0
    qtr3 = 0
    qtr4 = 0
    for month in range (1,13):
        sales = getMonthlySales(month)
        if month <= 3:
            qtr1 += sales
        elif month <= 6:
            qtr2 += sales
        elif month <= 9:
            qtr3 += sales
        else:
            qtr4 += sales
    print("Qtr 1 Sales:",qtr1)
    print("Qtr 2 Sales:",qtr2)
    print("Qtr 3 Sales:",qtr3)
    print("Qtr 4 Sales:",qtr4)
main()