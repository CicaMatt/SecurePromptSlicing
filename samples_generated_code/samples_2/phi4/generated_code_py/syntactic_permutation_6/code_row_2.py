vehicles = ["car", "truck", "motorcycle", "bicycle", "bus"]

index = int(input("Enter the index of the vehicle you want: "))
if 0 <= index < len(vehicles):
    selected_vehicle = vehicles[index]
    print(f"You selected: {selected_vehicle}")
else:
    print("Invalid index.")

for i, vehicle in enumerate(vehicles):
    print(f"Vehicle {i}: {vehicle}")