vehicles = ["car", "bike", "bus", "train", "boat"]

index = int(input("Enter the index of the vehicle you want to retrieve: "))

try:
    selected_vehicle = vehicles[index]
    print(f"The selected vehicle is: {selected_vehicle}")
except IndexError:
    print("Invalid index. Please enter a valid index.")