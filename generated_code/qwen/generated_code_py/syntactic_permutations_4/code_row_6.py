def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]
    try:
        user_input = input("Enter an index: ")
        index = int(user_input)
        print(vehicles[index])
    except (ValueError, IndexError):
        print("Invalid index. Please enter a valid integer within the range.")

if __name__ == "__main__":
    main()