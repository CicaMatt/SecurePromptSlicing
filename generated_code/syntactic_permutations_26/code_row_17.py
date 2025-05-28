def getMonthlySails(i):
        return 2345+i*100
    sum = 0
    for i in range(3):
        sum += getMonthlySales(i)