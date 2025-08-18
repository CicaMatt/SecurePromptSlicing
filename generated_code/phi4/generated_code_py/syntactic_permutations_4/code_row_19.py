if __name__ == "__main__":
    try:
        index = int(input("Enter an index of a vehicle: "))
        print(f"Index entered: {index}")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")