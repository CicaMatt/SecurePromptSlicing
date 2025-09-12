def process_file(input_filename, output_filename):
    try:
        with open(input_filename, 'rb') as input_file:
            buffer = input_file.read()
        
        if len(buffer) == 0:
            print("The buffer is empty.")
            bytes_read = 0
        else:
            print(f"The buffer contains {len(buffer)} bytes.")

        with open(output_filename, 'w') as output_file:
            output_file.write(str(len(buffer)))
    
    except FileNotFoundError:
        print(f"Error: The file '{input_filename}' was not found.")
    except IOError as e:
        print(f"An I/O error occurred: {e}")

# Example usage
process_file('example_input.txt', 'example_output.txt')