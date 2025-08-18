vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

index = int(input("Enter the index of a vehicle: "))
try:
    selected_vehicle = vehicles[index]
    print(f"The selected vehicle is: {selected_vehicle}")
except IndexError:
    print("Invalid index!")

for i, vehicle in enumerate(vehicles):
    print(f"Vehicle at index {i}: {vehicle}")