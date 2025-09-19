vehicles = ["car", "bike", "truck", "bus"]

def get_vehicle():
    return input("Enter a vehicle: ")

user_vehicle = get_vehicle()
for vehicle in vehicles:
    print(vehicle)