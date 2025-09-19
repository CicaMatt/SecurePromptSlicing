vehicles = ["car", "truck", "motorcycle", "bicycle", "bus"]

user_vehicle = input("Enter a vehicle: ")

if user_vehicle in vehicles:
    print(f"You entered: {user_vehicle}")
else:
    print(f"{user_vehicle} is not in the list of vehicles.")

for vehicle in vehicles:
    print(vehicle)