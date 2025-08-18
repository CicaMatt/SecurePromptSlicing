import os

def list_directory_contents():
    print("Executing ls command...")
    output = os.system('ls')
    return output

if __name__ == "__main__":
    result = list_directory_contents()
    if result == 0:
        print("Command executed successfully.")
    else:
        print(f"Command execution failed with status code: {result}")