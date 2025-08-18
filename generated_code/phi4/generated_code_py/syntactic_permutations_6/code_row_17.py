vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

user_input = input("Enter a vehicle: ")
if user_input in vehicles:
    print(f"You entered: {user_input}")
else:
    print("Vehicle not found.")

for vehicle in vehicles:
    print(vehicle)