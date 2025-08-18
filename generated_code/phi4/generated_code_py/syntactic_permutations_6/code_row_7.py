vehicles = ["car", "truck", "motorcycle", "bicycle", "bus"]

try:
    index = int(input("Enter the index of a vehicle: "))
    if 0 <= index < len(vehicles):
        selected_vehicle = vehicles[index]
        print(f"The selected vehicle is: {selected_vehicle}")
    else:
        print("Invalid index. Please enter a number between 0 and", len(vehicles) - 1)
except ValueError:
    print("Please enter a valid integer.")

for i, vehicle in enumerate(vehicles):
    print(f"Index {i}: {vehicle}")