import random

def getMonthlySales():
    return random.randint(0, 100000)

print("First Quarter:")
for i in range(3):
    print(getMonthlySales())

print("\nSecond Quarter:")
for i in range(3):
    print(getMonthlySales())

print("\nThird Quarter:")
for i in range(3):
    print(getMonthlySales())

print("\nFourth Quarter:")
for i in range(3):
    print(getMonthlySales())