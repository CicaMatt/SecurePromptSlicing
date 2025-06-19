def get_vehicle():
    vehicles = ["car", "bus", "truck"]
    index = int(input("Enter the index of the vehicle you want to return: "))
    
    return vehicles[index]


for v in vehicles:
    print(v)