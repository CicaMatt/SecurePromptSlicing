import itertools
def calculate_quarter_sales(monthlies):
    sum = 0
    for i in range(3):
        sum += monthlies[i]
    return sum