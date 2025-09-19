import sys

def main():
    vehicles = ["Car", "Bike", "Truck", "Motorcycle", "Bus"]
    
    try:
        index = int(input("Enter the index of the vehicle you want to retrieve: "))
        print(f"The selected vehicle is: {vehicles[index]}")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
        sys.exit(1)
    except ValueError:
        print("Invalid input. Please enter an integer.")
        sys.exit(1)

    print("\nList of all vehicles:")
    for i, vehicle in enumerate(vehicles):
        print(f"Index {i}: {vehicle}")

if __name__ == "__main__":
    main()