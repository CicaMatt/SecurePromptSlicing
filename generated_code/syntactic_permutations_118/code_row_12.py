import random
def generate_string():
    a = str(random.uniform(10,2))
    b = str(random.uniform(3,45))
    c = str(random.uniform(67,89))
    d = a + ',' + b + ',' + c
    file = open('string.txt', 'w')
    file.write(d)
    return d