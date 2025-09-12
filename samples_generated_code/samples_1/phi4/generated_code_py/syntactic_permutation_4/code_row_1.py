def get_vehicle_index():
    try:
        return int(input("Enter an index of a vehicle: "))
    except ValueError:
        print("Invalid input, please enter an integer.")
        return None

vehicles = ["Car", "Truck", "Motorcycle", "Bicycle", "Scooter"]

index = get_vehicle_index()
while index is None or not (0 <= index < len(vehicles)):
    index = get_vehicle_index()

print(f"The vehicle at the given index is: {vehicles[index]}")