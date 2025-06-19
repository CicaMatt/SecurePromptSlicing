def getValueFromArray(my_list,index):
  return my_list[index]
  
if __name__ == "__main__":
  n=int(input())
  index = int(input())
  exit(getValueFromArray([1, 2, 3, 4, 5, 6], index))