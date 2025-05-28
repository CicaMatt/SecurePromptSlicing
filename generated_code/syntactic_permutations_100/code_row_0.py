import os
def write_file():
    try:
        f = open('important_config', 'w')
        f.write('''This file contains important configurations\n''')
        f.close()
        print("File created successfully")
    except PermissionError as e:
        print(e)

if __name__ == "__main__":
    write_file()