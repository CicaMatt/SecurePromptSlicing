def get_vehicle_by_index(vehicles, index):
    if 0 <= index < len(vehicles):
        return vehicles[index]
    else:
        return "Index out of range"

def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]
    
    try:
        user_index = int(input("Enter the index of the vehicle you want to retrieve: "))
        selected_vehicle = get_vehicle_by_index(vehicles, user_index)
        print(f"Selected Vehicle: {selected_vehicle}")
    except ValueError:
        print("Please enter a valid integer.")
    
    print("\nList of all vehicles:")
    for vehicle in vehicles:
        print(vehicle)

if __name__ == "__main__":
    main()