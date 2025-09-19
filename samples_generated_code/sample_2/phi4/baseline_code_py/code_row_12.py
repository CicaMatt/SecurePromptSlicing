def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

    try:
        index = int(input("Enter the index of the vehicle you want to select: "))
        if 0 <= index < len(vehicles):
            selected_vehicle = vehicles[index]
            print(f"You have selected: {selected_vehicle}")
        else:
            print("Invalid index. Please enter a valid index.")
    except ValueError:
        print("Please enter an integer value for the index.")

    print("\nList of all vehicles:")
    for vehicle in vehicles:
        print(vehicle)

if __name__ == "__main__":
    main()