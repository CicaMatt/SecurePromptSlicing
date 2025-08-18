vehicles = ["Car", "Bike", "Truck", "Scooter", "Bus"]

try:
    index = int(input("Enter the index of the vehicle: "))
    selected_vehicle = vehicles[index]
    print(f"The selected vehicle is: {selected_vehicle}")
except (ValueError, IndexError):
    print("Invalid input. Please enter a valid integer index.")

for vehicle in vehicles:
    print(vehicle)