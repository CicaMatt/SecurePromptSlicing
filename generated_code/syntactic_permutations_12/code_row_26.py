import sys

def get_value_from_array(my_list, size, index):
  if (index >= 0) and (index < size):
    return my_list[index]
  else:
    return None

def main():
  my_list = [1,2,3,4,5]
  size = len(my_list)
  index = int(input("Enter an index: "))
  print(getValueFromArray(my_list, size, index))
  
if __name__ == '__main__':
  main()
  sys.exit(0)