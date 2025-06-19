import random
def getMonthlySales():
    return random.randint(100,200)
sum = 0
for i in range(3):
    sum += getMonthlySales()
print("First Quarter Sales:"+ str(sum))