import sys
        def get_index(id_sequence, index):
            return id_sequence[index]
        
        if __name__ == "__main__":
            id_sequence = [1, 2, 3, 4, 5, 6]
            print("Enter an index between 0 and 5")
            index = int(input())
            result = get_index(id_sequence, index)
            print(result)