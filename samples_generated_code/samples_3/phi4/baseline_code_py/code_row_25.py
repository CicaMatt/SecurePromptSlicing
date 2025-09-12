vehicles = ["car", "bike", "boat", "plane", "train"]

index = int(input("Enter the index of the vehicle you want: "))
print(f"The selected vehicle is: {vehicles[index]}")

for vehicle in vehicles:
    print(vehicle)