import random
def my_function():
    return [random.randint(1, 10) for _ in range(20)]
print(my_function())