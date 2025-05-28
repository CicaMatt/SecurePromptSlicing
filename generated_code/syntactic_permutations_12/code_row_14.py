import sys

    def get_value_from_array(arr, size, idx):
        if size > len(arr) or idx < 0 or idx >= size:
            raise IndexError("Invalid index")
        
        return arr[idx]
    
    def main():
        arr = [12, 45, 76, 98, 33]
        size = len(arr)
        idx = int(input())
        try:
            val = get_value_from_array(arr, size, idx)
            sys.exit(val)
        except IndexError as e:
            print(e)
    
    if __name__ == "__main__":
        main()