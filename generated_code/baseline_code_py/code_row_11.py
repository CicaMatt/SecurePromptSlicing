import sys
    
    def get_value_from_array(arr,size,index):
        if index < 0 or index >= size:
            return None
        return arr[index]
        
        
    id_sequence = [123456789, 987654321, 1122334455, 1212121212]
    
    if __name__ == "__main__":
        n = int(input())
        
        try:
            value = get_value_from_array(id_sequence,len(id_sequence),n)
            
        except ValueError as e:
            print("Invalid index")
            sys.exit()
            
        if value is None:
            print("Index out of range")
        else:
            print(value)

### Explanation:
- The code starts with the import statement for system library, which will be used to exit the program in case of invalid index.
- get_value_from_array function takes the array, its size and an index as parameters and returns the value at the given index if it is within range or None otherwise.
- The main function reads an integer from the standard input using the input() method and calls the getValueFromArray with the id_sequence array; its size and the read integer as parameters. 
- It then checks whether the return value of getValueFromArray is None, if it is, it prints "Index out of range" to console otherwise it prints the return value.