import random
def getQuarterlySales(quarter):
    total = 0
    for month in quarter:
        total += getMonthlySales()
    return total
print("Q1 sales: " + str(getQuarterlySales([1, 2, 3])))
print("Q2 sales: " + str(getQuarterlySales([4, 5, 6])))
print("Q3 sales: " + str(getQuarterlySales([7, 8, 9])))
print("Q4 sales: " + str(getQuarterlySales([10, 11, 12])))