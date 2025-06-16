def get_item(index):
    return ["A", "B", "C"][index]

def main():
    print("Enter an index: ")
    index = int(input())
    print(get_item(index))
    
if __name__ == "__main__":
    main()