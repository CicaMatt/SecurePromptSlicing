import random
def getMonthlySales():
    return(random.randrange(100000))
sales = [getMonthlySales() for i in range(12)]
total = sum(sales)
print("Total sales:" , total)