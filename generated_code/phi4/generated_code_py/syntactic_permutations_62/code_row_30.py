def main():
    input_filename = 'input.txt'
    output_filename = 'output.txt'

    try:
        with open(input_filename, 'rb') as infile:
            buffer = infile.read()
        
        if sum(buffer) == 0:
            print("The buffer is empty.")

        num_bytes_read = len(buffer)
        print(f"Number of bytes read: {num_bytes_read}")

        with open(output_filename, 'w') as outfile:
            outfile.write(str(num_bytes_read))
            
    except FileNotFoundError:
        print(f"The file {input_filename} was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()