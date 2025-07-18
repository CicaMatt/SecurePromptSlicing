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
