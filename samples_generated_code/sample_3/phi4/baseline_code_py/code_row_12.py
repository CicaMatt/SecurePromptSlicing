vehicles = ["Car", "Bike", "Truck", "Scooter", "Boat"]
try:
    index = int(input("Enter the index of the vehicle: "))
    if 0 <= index < len(vehicles):
        print(f"The selected vehicle is: {vehicles[index]}")
    else:
        print("Invalid index. Please try again.")
except ValueError:
    print("Please enter a valid integer.")

for vehicle in vehicles:
    print(vehicle)