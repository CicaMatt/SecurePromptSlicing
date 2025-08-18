def main():
    vehicles = ["car", "bike", "truck", "bus", "train"]
    
    try:
        index = int(input("Enter the index of a vehicle: "))
        if 0 <= index < len(vehicles):
            print(f"The selected vehicle is: {vehicles[index]}")
        else:
            print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

if __name__ == "__main__":
    main()