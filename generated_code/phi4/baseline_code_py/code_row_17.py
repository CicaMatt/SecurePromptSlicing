def get_value_from_user_input():
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    try:
        user_index = int(input("Enter an index: "))
        
        if 0 <= user_index < len(array):
            print(f"The value at index {user_index} is {array[user_index]}")
        else:
            print("Index out of range. Please enter a valid index between 0 and {}.".format(len(array) - 1))
    
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_from_user_input()