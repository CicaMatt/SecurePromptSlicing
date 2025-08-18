def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]
    try:
        index = int(input("Enter an index of a vehicle: "))
        print(vehicles[index])
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

if __name__ == "__main__":
    main()