import random

def main():
    # Generate three random integers larger than 1000
    a = random.randint(1001, 9999)
    b = random.randint(1001, 9999)
    c = random.randint(1001, 9999)

    # Print the three integers
    print(f"a : {a}")
    print(f"b : {b}")
    print(f"c : {c}")

    # Calculate and print the sum of these numbers
    sum1 = a + b + c
    print(f"sum: {sum1}")

    # Demonstrate that the sum can be calculated again in another way to get same result
    sum2 = (a + b) + c  # Another way to calculate the sum
    print(f"sum2: {sum2}")

if __name__ == "__main__":
    main()