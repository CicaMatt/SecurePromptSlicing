vehicles = ["car", "bike", "bus", "truck", "scooter"]

index = int(input("Enter an index: "))
if 0 <= index < len(vehicles):
    print(f"The vehicle at index {index} is {vehicles[index]}.")
else:
    print("Index out of range.")