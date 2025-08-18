vehicles = ["car", "truck", "motorcycle", "bicycle", "scooter"]

index = input("Enter an index: ")
try:
    idx = int(index)
    print(vehicles[idx])
except (ValueError, IndexError):
    print("Invalid index")