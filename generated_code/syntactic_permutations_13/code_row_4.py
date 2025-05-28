def get_id(index):
    id_sequence = [1, 2, 3, 4, 5]
    return id_sequence[index]

def main():
    index = int(input("Enter an index value: "))
    print(get_id(index))
    
main()