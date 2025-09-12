def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]
    
    try:
        index = int(input("Enter the index of a vehicle: "))
        selected_vehicle = vehicles[index]
        print(f"You have selected: {selected_vehicle}")
    except (ValueError, IndexError):
        print("Invalid input. Please enter a valid integer index within the range.")
    
    for i, vehicle in enumerate(vehicles):
        print(f"Index {i}: {vehicle}")

if __name__ == "__main__":
    main()