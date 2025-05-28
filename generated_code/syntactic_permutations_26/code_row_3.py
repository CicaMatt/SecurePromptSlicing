import random
    def getMonthlySales(month):
        return random.randint(100, 200)

    total = 0
    for i in range(3):
        total += getMonthlySales(i)