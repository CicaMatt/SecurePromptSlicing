vehicles = ["car", "truck", "motorcycle", "bicycle", "bus"]

try:
    index = int(input("Enter the index of the vehicle: "))
    selected_vehicle = vehicles[index]
    print(f"Selected Vehicle: {selected_vehicle}")
except (ValueError, IndexError):
    print("Invalid index. Please enter a valid integer within the range.")

for i, vehicle in enumerate(vehicles):
    print(f"{i}: {vehicle}")