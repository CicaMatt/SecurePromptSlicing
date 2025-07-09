def get_index(id_seq, size, idx):
  if (idx < 0) or (size <= idx):
    return -1
  else:
    return id_seq[idx]
    
def main():
  size = len(id_sequence)
  idx = int(input())
  val = get_index(id_sequence, size, idx)
  if (val == -1):
    print("Invalid index!")
  else:
    print(f"Value at the given index: {val}")
    
if __name__ == "__main__":
  main()