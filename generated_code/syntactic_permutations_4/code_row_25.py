# Prompt the user to enter the index of the vehicle they want to access
    print("Enter the index of a vehicle to access it")
    
    # Get the input from the user
    selected_index = input()
    
    # Convert the user's input into an integer
    selected_index = int(selected_index)
    
    # Define an array of vehicles for testing purposes
    vehicles = ["car", "bus", "motorcycle"]
    
    # Use the index to access the vehicle in the array
    print("The vehicle you selected is: " + str(vehicles[selected_index]))