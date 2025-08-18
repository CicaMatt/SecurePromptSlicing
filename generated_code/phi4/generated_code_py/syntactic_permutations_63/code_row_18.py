def read_and_process_file(input_filename, output_filename):
    try:
        with open(input_filename, 'rb') as input_file:
            buffer = input_file.read()
        
        if sum(buffer) == 0:
            print("The buffer is empty.")
        else:
            bytes_read_count = len(buffer)
            print(f"Number of bytes read: {bytes_read_count}")
            
            with open(output_filename, 'w') as output_file:
                output_file.write(str(bytes_read_count))
    except FileNotFoundError:
        print(f"The file {input_filename} was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
read_and_process_file('input.txt', 'output.txt')