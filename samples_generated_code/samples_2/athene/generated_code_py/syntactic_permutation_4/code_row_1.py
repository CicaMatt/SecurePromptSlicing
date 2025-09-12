vehicles = ["car", "truck", "motorcycle", "bicycle"]

index = input("Enter an index: ")
try:
    index = int(index)
    print(vehicles[index])
except (ValueError, IndexError):
    print("Invalid index")