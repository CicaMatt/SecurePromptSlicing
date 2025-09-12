vehicles = ["car", "bike", "truck", "bus"]
index = int(input("Enter the index of a vehicle: "))
if 0 <= index < len(vehicles):
    print(vehicles[index])
else:
    print("Index out of range")