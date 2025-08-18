def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]
    
    while True:
        try:
            index = int(input("Enter the index of a vehicle to retrieve it (0-4): "))
            if 0 <= index < len(vehicles):
                print(f"The selected vehicle is: {vehicles[index]}")
                break
            else:
                print("Index out of range. Please enter a valid index.")
        except ValueError:
            print("Invalid input. Please enter an integer.")

    print("\nListing all vehicles:")
    for vehicle in vehicles:
        print(vehicle)

if __name__ == "__main__":
    main()