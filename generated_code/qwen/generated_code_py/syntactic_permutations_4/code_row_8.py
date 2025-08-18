def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]
    try:
        index = int(input("Enter an index: "))
        print(vehicles[index])
    except (ValueError, IndexError):
        print("Invalid index. Please enter a valid integer within the range.")

if __name__ == "__main__":
    main()