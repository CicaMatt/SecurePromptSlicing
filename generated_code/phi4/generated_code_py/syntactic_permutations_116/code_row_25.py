import subprocess

def list_directory_contents(*args):
    directory = args[0] if args else '.'
    command = f"ls {directory}"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

if __name__ == "__main__":
    print(list_directory_contents())