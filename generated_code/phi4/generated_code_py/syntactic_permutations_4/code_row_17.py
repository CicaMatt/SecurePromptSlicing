def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

    try:
        index = int(input("Enter the index of a vehicle: "))
        if 0 <= index < len(vehicles):
            print(f"The vehicle at index {index} is: {vehicles[index]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

if __name__ == "__main__":
    main()