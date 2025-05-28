def get_id(index):
    id_sequence = ["123-456-789","234-567-890","345-678-901"]
    return id_sequence[index]

main():
    index = int(input("Enter an index: "))
    print(get_id(index))