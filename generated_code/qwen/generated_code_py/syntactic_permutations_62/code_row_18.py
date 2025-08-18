def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    try:
        with open(input_file_path, 'rb') as file:
            buffer = file.read()
            num_bytes_read = len(buffer)

        if num_bytes_read == 0:
            buffer_content = "The buffer is empty."
        else:
            buffer_content = f"Number of bytes read: {num_bytes_read}"

        with open(output_file_path, 'w') as file:
            file.write(buffer_content)

    except FileNotFoundError:
        print(f"The file {input_file_path} does not exist.")

if __name__ == "__main__":
    main()