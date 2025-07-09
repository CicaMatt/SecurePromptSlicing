def get_id(index):
    return id_sequence[index]

def main():
    index = int(input("Enter an index: "))
    print(get_id(index))

if __name__ == "__main__":
    main()