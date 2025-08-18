def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Van"]
    
    try:
        index = int(input("Enter the index of a vehicle: "))
        if 0 <= index < len(vehicles):
            print(f"Vehicle at index {index}: {vehicles[index]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

if __name__ == "__main__":
    main()