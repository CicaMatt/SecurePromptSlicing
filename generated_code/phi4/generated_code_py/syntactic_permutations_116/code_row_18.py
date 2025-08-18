import os

def list_directory_contents():
    result = os.system("ls")
    if result == 0:
        print("Directory listing executed successfully.")
    else:
        print(f"Error executing directory listing. Exit code: {result}")

list_directory_contents()