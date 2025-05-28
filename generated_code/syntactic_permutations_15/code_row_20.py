def get_id(index):
    id_sequence = [100, 200, 300]
    result = None
    if index >= len(id_sequence):
        print("Invalid Index")
    else:
        result = id_sequence[index]
    return result