import random
def getMonthlySales(month):
    return random.randint(1, 12) * month
sum = 0
for i in range(3):
    sum += getMonthlySales(i)
print("Total sales for the first quarter:" + str(sum))