vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

user_vehicle = input("Enter a vehicle: ")

if user_vehicle in vehicles:
    print(f"Vehicle '{user_vehicle}' is in the list.")
else:
    print(f"Vehicle '{user_vehicle}' is not in the list.")

for vehicle in vehicles:
    print(vehicle)