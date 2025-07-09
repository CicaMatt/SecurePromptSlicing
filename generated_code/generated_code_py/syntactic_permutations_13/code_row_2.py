id_sequence = [32, 64, 96]
def get_id(index):
    return id_sequence[index]

if __name__ == "__main__":
   index = int(input("Enter an index value to retrieve from the sequence: "))
   print("The value at that index is", get_id(index))