def get_id(index):
    id_sequence = [1234, 8765, 9012]
    if index < len(id_sequence):
        return id_sequence[index]
    else:
        return -1
        
def main():
    index = int(input("Enter the index: "))
    value = get_id(index)
    print(value)
    
main()