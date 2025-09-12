def main():
    vehicles = ["Car", "Bike", "Truck", "Scooter", "Bus"]
    
    try:
        index = int(input("Enter the index of a vehicle: "))
        if 0 <= index < len(vehicles):
            print(f"Vehicle at index {index}: {vehicles[index]}")
        else:
            print("Invalid index.")
            
    except ValueError:
        print("Please enter a valid integer.")

    for i, vehicle in enumerate(vehicles):
        print(f"Index {i}: {vehicle}")

if __name__ == "__main__":
    main()