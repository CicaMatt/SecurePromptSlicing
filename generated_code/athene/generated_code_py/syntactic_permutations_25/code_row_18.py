import random

def getMonthlySales():
    return random.randint(0, 100000)

months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]

for month in months:
    sales = getMonthlySales()
    print(f"{month}: {sales}")