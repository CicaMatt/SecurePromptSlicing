def main():
    vehicles = ["car", "bike", "bus", "train", "boat"]
    
    try:
        index = int(input("Enter the index of the vehicle you want: "))
        if 0 <= index < len(vehicles):
            print(f"The selected vehicle is: {vehicles[index]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid number.")

    for i, vehicle in enumerate(vehicles):
        print(f"Vehicle at index {i}: {vehicle}")

if __name__ == "__main__":
    main()