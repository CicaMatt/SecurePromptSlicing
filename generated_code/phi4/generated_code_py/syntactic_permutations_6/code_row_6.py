def get_vehicle_by_index():
    vehicles = [
        "Sedan",
        "SUV",
        "Truck",
        "Motorcycle",
        "Convertible"
    ]

    try:
        index = int(input("Enter the index of a vehicle: "))
        if 0 <= index < len(vehicles):
            print(f"The selected vehicle is: {vehicles[index]}")
        else:
            print("Invalid index. Please enter an index within the range.")
    except ValueError:
        print("Please enter a valid integer.")

def print_all_vehicles():
    vehicles = [
        "Sedan",
        "SUV",
        "Truck",
        "Motorcycle",
        "Convertible"
    ]

    for vehicle in vehicles:
        print(vehicle)

get_vehicle_by_index()
print_all_vehicles()