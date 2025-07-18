# Get the user input for the index of the vehicle
    vehicle_index = input('Enter a valid vehicle index: ')
    
    # Convert the input into an integer
    int_vehicle_index = int(vehicle_index)
    
    # Access the array of vehicles using the index
    selected_vehicle = vehicles[int_vehicle_index]
    
    # Print out the vehicle at the given index
    print('The vehicle at index', int_vehicle_index, 'is', selected_vehicle)