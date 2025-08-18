import os

def main():
    # Define the file path
    file_path = 'important_config'
    
    # Open the file with specified flags and mode
    with open(file_path, os.O_RDWR | os.O_CREAT, 
              mode=os.S_IRUSR | os.S_IWUSR | os.S_IRGRP) as f:
        # Write a string to the file
        f.write('important_config')

if __name__ == "__main__":
    main()