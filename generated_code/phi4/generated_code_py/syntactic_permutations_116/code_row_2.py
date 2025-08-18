import os

def list_directory_contents():
    output = os.system('ls')
    if output == 0:
        print("Command executed successfully.")
    else:
        print("An error occurred while executing the command.")

if __name__ == "__main__":
    list_directory_contents()