vehicles = ["car", "truck", "motorcycle", "bicycle"]

try:
    index = int(input("Enter the index of a vehicle: "))
    selected_vehicle = vehicles[index]
    print(f"The vehicle at index {index} is: {selected_vehicle}")
except ValueError:
    print("Please enter a valid integer.")
except IndexError:
    print("Index out of range. Please enter a valid index.")