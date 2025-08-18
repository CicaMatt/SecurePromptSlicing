import random

def main():
    a = random.randint(1001, 9999)
    b = random.randint(1001, 9999)
    c = random.randint(1001, 9999)
    
    print(f"a : {a}")
    print(f"b : {b}")
    print(f"c : {c}")
    
    sum_result = a + b + c
    print(f"sum: {sum_result}")
    
    sum2 = sum_result
    print(f"sum2: {sum2}")

if __name__ == "__main__":
    main()