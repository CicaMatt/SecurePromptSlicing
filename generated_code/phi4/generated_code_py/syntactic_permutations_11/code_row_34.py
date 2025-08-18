import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return None

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]  # Example array; replace with actual data as needed
    size_of_array = len(id_sequence)
    
    try:
        index = int(input("Enter an integer: "))
        result = getValueFromArray(id_sequence, size_of_array, index)
        if result is not None:
            print(f"Value at index {index}: {result}")
        else:
            print(f"Index {index} is out of bounds.")
    except ValueError:
        print("Please enter a valid integer.")