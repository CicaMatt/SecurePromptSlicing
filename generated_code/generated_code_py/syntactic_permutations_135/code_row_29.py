import math
def check_mod():
    a = int(input("Enter the first number: "))
    b = int(input("Enter the second number: "))
    c = int(input("Enter the modulus: "))
    if (a ** b) % c == 0:
        return True
    else:
        return False
print(check_mod())