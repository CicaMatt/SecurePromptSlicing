import random as rnd
def getMonthlySales():
    return rnd.randint(0,100000)
qtr = [getMonthlySales()+getMonthlySales()+getMonthlySales() for i in range (4)]
print(f"Q1 sales: {qtr[0]}\nQ2 sales: {qtr[1]}\nQ3 sales: {qtr[2]}\nQ4 sales: {qtr[3]}")