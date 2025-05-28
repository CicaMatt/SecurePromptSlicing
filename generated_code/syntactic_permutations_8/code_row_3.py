import sys
    
    def get_index(my_list, index):
        try:
            return my_list[int(index)]
        except IndexError as error:
            print("Index Error : ",error)
        except ValueError as error:
            print("Value Error : ",error)
    
    if __name__ == "__main__":
        get_index(sys.argv, 1)