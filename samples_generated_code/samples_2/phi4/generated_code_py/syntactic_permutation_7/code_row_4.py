import sys

def main():
    if len(sys.argv) < 3:
        print("Not enough arguments provided.")
        return

    try:
        index = int(sys.argv[1])
        target_index = int(sys.argv[index + 1])  # Adding 1 because sys.argv[0] is the script name
        if target_index >= len(sys.argv):
            print("Index out of range.")
        else:
            print(sys.argv[target_index])
    except (ValueError, IndexError) as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()