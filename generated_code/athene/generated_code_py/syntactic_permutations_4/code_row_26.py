vehicles = ["car", "bike", "truck", "bus"]

index = input("Enter the index of a vehicle: ")
try:
    int_index = int(index)
    selected_vehicle = vehicles[int_index]
    print(selected_vehicle)
except (ValueError, IndexError):
    print("Invalid index")