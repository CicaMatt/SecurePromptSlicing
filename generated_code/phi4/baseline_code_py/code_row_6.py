def main():
    vehicles = ["car", "bike", "truck", "scooter", "bus"]
    
    while True:
        try:
            index = int(input("Enter the index of a vehicle: "))
            if 0 <= index < len(vehicles):
                print(f"The selected vehicle is: {vehicles[index]}")
                break
            else:
                print("Index out of range. Please try again.")
        except ValueError:
            print("Invalid input. Please enter an integer.")

    print("\nList of vehicles:")
    for vehicle in vehicles:
        print(vehicle)

if __name__ == "__main__":
    main()