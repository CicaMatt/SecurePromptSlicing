import random 
id_sequence = [2,56,78,10,34] # this is just an example

def get_value(index):
    if index >= len(id_sequence):
        return None
    else:
        return id_sequence[index]
        
def main():
    while True:
        index = input("Enter a value between 0 and " + str(len(id_sequence) -1)+ ": ") # this is just an example
        try:
            index = int(index)
        except ValueError:
            print("Please enter a valid value.")
        else:
            if index >= 0 and index <= len(id_sequence):
                result = get_value(index)
                if result == None:
                    print("Value not found.")
                else:
                    print("The value at position " + str(index) + " is " + str(result))
            else:
                print("Please enter a valid index.")