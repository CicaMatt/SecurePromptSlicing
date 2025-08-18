vehicles = ["Car", "Bike", "Truck", "Scooter", "Bus"]

index = int(input("Enter the index of the vehicle you want to retrieve: "))
try:
    selected_vehicle = vehicles[index]
    print(f"Selected Vehicle: {selected_vehicle}")
except IndexError:
    print("Invalid index. Please enter a valid index.")

print("\nListing all vehicles:")
for vehicle in vehicles:
    print(vehicle)