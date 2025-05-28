from random import randint
import numpy as np

def getMonthlySales():
    return np.random.randint(10, 50)
    
for i in range(12):
    sales = getMonthlySales()
    print("The monthly sales for this quarter is:", sales)