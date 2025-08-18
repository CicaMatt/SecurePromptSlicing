vehicles = ["car", "truck", "motorcycle", "bicycle", "bus"]

user_vehicle = input("Enter a vehicle: ")

if user_vehicle in vehicles:
    print(f"Vehicle found: {user_vehicle}")
else:
    print(f"Vehicle not found: {user_vehicle}")

for vehicle in vehicles:
    print(vehicle)