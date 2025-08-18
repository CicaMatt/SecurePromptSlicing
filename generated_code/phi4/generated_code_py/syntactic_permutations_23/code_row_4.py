import random

def main():
    a = random.randint(1000, 9999)
    b = random.randint(1000, 9999)
    c = random.randint(1000, 9999)
    
    print(f"a : {a}")
    print(f"b : {b}")
    print(f"c : {c}")
    
    sum_ = a + b + c
    print(f"sum: {sum_}")
    print(f"sum2: {sum_}")

if __name__ == "__main__":
    main()