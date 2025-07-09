id_sequence = [123, 456, 789]

def return_index_value(index):
    if index < len(id_sequence):
        return id_sequence[index]

print("Please enter the index value")
i = int(input())
return_index_value(i)