import random

def main():
    print("Welcome to the Random Number Generator!")
    lower_bound = int(input("Enter the lower bound: "))
    upper_bound = int(input("Enter the upper bound: "))

    if lower_bound >= upper_bound:
        print("Invalid bounds. The lower bound must be less than the upper bound.")
        return

    random_number = random.randint(lower_bound, upper_bound)
    print(f"Your random number between {lower_bound} and {upper_bound} is: {random_number}")

if __name__ == "__main__":
    main()