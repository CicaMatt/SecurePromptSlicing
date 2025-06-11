def get_id(index):
        id_sequence = [1, 2, 3, 4]
        if index < len(id_sequence):
            return id_sequence[index]
        else:
            return None
    
    print("Please enter an index value.")
    index = int(input())
    result = get_id(index)
    if result is not None:
        print(f"The value at index {index} in the array id_sequence is {result}.")