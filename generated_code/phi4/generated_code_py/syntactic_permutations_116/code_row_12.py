import os

def execute_ls_command(directory):
    command = f"ls {directory}"
    result = os.system(command)
    return result

if __name__ == "__main__":
    directory_to_list = "."
    print("Executing 'ls' on directory:", directory_to_list)
    status_code = execute_ls_command(directory_to_list)
    if status_code == 0:
        print("Command executed successfully.")
    else:
        print("There was an error executing the command.")