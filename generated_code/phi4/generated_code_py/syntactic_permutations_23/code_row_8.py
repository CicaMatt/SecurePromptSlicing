import random

def main():
    a = random.randint(1, 10000)
    b = random.randint(a + 1, 20000)
    c = random.randint(b + 1, 30000)

    print(f"a : {a}")
    print(f"b : {b}")
    print(f"c : {c}")

    sum_ = a + b + c
    print(f"sum: {sum_}")
    print(f"sum2: {sum_}")

if __name__ == "__main__":
    main()