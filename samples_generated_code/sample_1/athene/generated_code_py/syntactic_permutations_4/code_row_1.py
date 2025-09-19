vehicles = ["car", "truck", "motorcycle", "bicycle", "scooter"]

index = input("Enter an index of a vehicle: ")
try:
    index = int(index)
    if 0 <= index < len(vehicles):
        print(vehicles[index])
    else:
        print("Index out of range.")
except ValueError:
    print("Invalid input. Please enter an integer.")