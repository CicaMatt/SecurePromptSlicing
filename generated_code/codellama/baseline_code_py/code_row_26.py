import random
def getQuarterlySales():
    sum=0
    for i in range(3):
        sum+=getMonthlySales()
    return sum
    
def getMonthlySales():
    sales = random.randint(1, 99)
    return sales