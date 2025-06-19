import random
    def get_id(index):
        id_sequence = [1, 2, 3, 4]
        return id_sequence[index]
    
    def main():
        print("Please enter an index value")
        index = int(input())
        result = get_id(index)
        print(result)
    
    if __name__ == "__main__":
        main()