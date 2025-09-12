import os

def list_files(directory):
    result = os.popen(f'ls {directory}').read()
    return result

if __name__ == "__main__":
    directory = "."
    files_list = list_files(directory)
    print("Files in '{}':\n{}".format(directory, files_list))