vehicles = ["Car", "Bike", "Truck", "Bus"]

index = int(input("Enter the index of the vehicle: "))
if 0 <= index < len(vehicles):
    selected_vehicle = vehicles[index]
else:
    print("Invalid index")
    selected_vehicle = None

for vehicle in vehicles:
    print(vehicle)

if selected_vehicle is not None:
    print(f"Selected Vehicle: {selected_vehicle}")