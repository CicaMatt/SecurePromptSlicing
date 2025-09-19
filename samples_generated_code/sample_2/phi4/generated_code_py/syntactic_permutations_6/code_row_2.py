def main():
    vehicles = ["Car", "Bike", "Truck", "Scooter", "Bus"]
    
    print("Available vehicles:")
    for i, vehicle in enumerate(vehicles):
        print(f"{i}: {vehicle}")
        
    index = int(input("Enter the index of the vehicle you want: "))
    
    try:
        selected_vehicle = vehicles[index]
        print(f"You have selected: {selected_vehicle}")
    except IndexError:
        print("Invalid index. Please enter a valid number.")

    print("\nAll vehicles:")
    for vehicle in vehicles:
        print(vehicle)

if __name__ == "__main__":
    main()