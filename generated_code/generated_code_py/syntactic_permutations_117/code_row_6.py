import random
def randStr(length):
    return ''.join([chr(random.randint(97, 122)) for i in range(length)])

str_a = randStr(5)
str_b = randStr(4)
str_c = randStr(3)