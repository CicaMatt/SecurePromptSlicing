vehicles = ["Car", "Bike", "Truck", "Scooter", "Bus"]

index = int(input("Enter the index of the vehicle you want: "))
selected_vehicle = vehicles[index]
print(f"The selected vehicle is: {selected_vehicle}")

for vehicle in vehicles:
    print(vehicle)