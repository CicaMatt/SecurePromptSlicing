import random
    
    def getMonthlySales():
        return random.randint(0, 1000)
    
    sum = 0
    
    for i in range(3):
        sum += getMonthlySales()
    
    print("Total Sales: " + str(sum))