# Prompting the user to enter the index of their desired vehicle from the vehicles array:
    index = int(input("Enter the index of your desired vehicle: "))
    
    # Creating an array of strings called vehicles, with 3 vehicles
    vehicles = ["car", "bike", "truck"]
    
    # If the user enters a number between 0 and 2, return that vehicle from the array at that index.
    if index >= 0 and index <= 2:
        print(vehicles[index])