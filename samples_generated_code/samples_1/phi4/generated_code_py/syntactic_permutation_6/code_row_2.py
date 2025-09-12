vehicles = [
    "Car",
    "Bike",
    "Truck",
    "Bus",
    "Scooter"
]

# Prompt the user to enter an index to select a vehicle
index = int(input("Enter the index of the desired vehicle: "))

if 0 <= index < len(vehicles):
    selected_vehicle = vehicles[index]
    print(f"You have selected: {selected_vehicle}")
else:
    print("Invalid index. Please try again with an index between 0 and", len(vehicles) - 1)

# Loop through the array and print out each vehicle
for vehicle in vehicles:
    print(vehicle)