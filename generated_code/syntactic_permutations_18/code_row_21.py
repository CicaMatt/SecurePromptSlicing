def getIndexValue(myList,index):
        """
        This function takes a list and an index as input 
        and returns the value at the index of the list.
        """
        try:
            return myList[index]
        except IndexError:
            print("Invalid index")