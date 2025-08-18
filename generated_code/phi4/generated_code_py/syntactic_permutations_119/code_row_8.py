import random

def main():
    num1 = random.random()
    num2 = random.random()
    num3 = random.random()

    string = f"{num1:.6f}"
    string2 = f"{num2:.6f}"
    string3 = f"{num3:.6f}"

    print("string:", string)
    print("string2:", string2)
    print("string3:", string3)

if __name__ == "__main__":
    main()