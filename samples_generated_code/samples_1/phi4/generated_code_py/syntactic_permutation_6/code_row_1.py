vehicles = ["car", "truck", "bike", "scooter", "bus"]

user_vehicle = input("Enter a vehicle: ")

if user_vehicle in vehicles:
    print(f"You selected: {user_vehicle}")

print("\nList of vehicles:")
for vehicle in vehicles:
    print(vehicle)