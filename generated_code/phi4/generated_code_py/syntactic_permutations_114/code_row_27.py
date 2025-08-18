import os

def list_files(directory):
    result = os.system(f'ls {directory}')
    return result

if __name__ == "__main__":
    directory = input("Enter the directory to list files: ")
    print(list_files(directory))