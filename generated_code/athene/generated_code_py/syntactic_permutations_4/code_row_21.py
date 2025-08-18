vehicles = ["car", "truck", "motorcycle", "bicycle", "bus"]

index = input("Enter an index of a vehicle: ")
try:
    index = int(index)
    print(vehicles[index])
except ValueError:
    print("Invalid index")
except IndexError:
    print("Index out of range")