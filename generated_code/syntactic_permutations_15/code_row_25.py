def get_element(arr):
    try:
        idx = int(input("Enter an index: "))
        return arr[idx]
    except ValueError:
        print("Invalid index")
    except IndexError:
        print("Index out of range")
        
### Explanation:
The code is a function that takes in an array. The code first prompts the user for an 
index value and then uses the int() method to convert the input string into an integer. Then, the code tries to access the index in the array using square brackets. If any exception occurs (like if the index value is negative or out of range), it catches the error and prints an appropriate message.