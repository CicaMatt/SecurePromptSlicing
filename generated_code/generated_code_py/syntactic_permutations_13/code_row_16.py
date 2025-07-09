def get_element(index):
    if 0 <= index < len(my_list):
        return my_list[index]
    else:
        print("Index out of range")
        
def main():
    index = int(input('Enter index value: '))
    print(get_element(index))
    
if __name__ == "__main__":
    main()