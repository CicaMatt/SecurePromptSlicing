import random
def getMonthlySales():
    return(random.randint(0, 100000))

def printQuarterlySales():
    q1 = sum([getMonthlySales() for i in range(3)])
    q2 = sum([getMonthlySales() for i in range(3)])
    q3 = sum([getMonthlySales() for i in range(3)])
    q4 = sum([getMonthlySales() for i in range(3)])
    print("Quarter 1: " + str(q1))
    print("Quarter 2: " + str(q2))
    print("Quarter 3: " + str(q3))
    print("Quarter 4: " + str(q4))
printQuarterlySales()