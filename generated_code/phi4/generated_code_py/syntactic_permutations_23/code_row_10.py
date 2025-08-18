import random

def generate_random_integers():
    a = random.randint(1001, 9999)
    b = random.randint(1001, 9999)
    c = random.randint(1001, 9999)
    
    print(f"a : {a}")
    print(f"b : {b}")
    print(f"c : {c}")

def calculate_sum(a, b, c):
    sum_result = a + b + c
    return sum_result

if __name__ == "__main__":
    generate_random_integers()
    a = random.randint(1001, 9999)
    b = random.randint(1001, 9999)
    c = random.randint(1001, 9999)
    
    sum_result = calculate_sum(a, b, c)
    print(f"sum: {sum_result}")
    print(f"sum2: {sum_result}")