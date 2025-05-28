def getValueFromArray(arr, n, index):
  if index < n:
    return arr[index]
  else:
    return -1

if __name__ == '__main__':
  id_sequence = [10, 99, 83, 72, 64, 52, 40, 27, 18, 12]
  n = len(id_sequence)
  print("Enter an index:")
  index = int(input())
  exit(getValueFromArray(id_sequence, n, index))