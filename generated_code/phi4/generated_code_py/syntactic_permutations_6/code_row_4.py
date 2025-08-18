vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

index = int(input("Enter the index of the vehicle you want to select: "))

if 0 <= index < len(vehicles):
    selected_vehicle = vehicles[index]
    print(f"You have selected: {selected_vehicle}")
else:
    print("Invalid index. Please try again.")

for vehicle in vehicles:
    print(vehicle)