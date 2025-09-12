vehicles = ["car", "motorcycle", "bicycle", "truck", "bus"]

index_input = input("Enter an index: ")
try:
    index = int(index_input)
    print(vehicles[index])
except (ValueError, IndexError):
    print("Invalid index")