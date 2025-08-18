def get_vehicle_index():
    try:
        index = int(input("Enter the index of the vehicle: "))
        return index
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        return None

vehicle_index = get_vehicle_index()
if vehicle_index is not None:
    print(f"You entered the index: {vehicle_index}")