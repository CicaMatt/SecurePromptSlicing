import sys 
    
    # Asking user for input 
    index = int(input("Enter vehicle index ")) 
    
    try: 
        # Accessing element using index in vehicles array 
        print(vehicles[index]) 
    except IndexError as e: 
        # Handling error if index is out of range 
        print("Index out of range!") 
    except Exception as e: 
        # Handling any other exception 
        print("Some other error occurred")