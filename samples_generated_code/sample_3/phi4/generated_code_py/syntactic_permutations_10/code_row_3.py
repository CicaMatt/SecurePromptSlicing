def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    return None

if __name__ == "__main__":
    import sys
    
    input_data = sys.stdin.read().strip()
    
    id_sequence = [1, 2, 3, 4, 5]  # Example array; change as needed
    index = int(input_data)
    result = getValueFromArray(id_sequence, len(id_sequence), index)
    print(result)