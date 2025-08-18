import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout if result.returncode == 0 else f"Error: {result.stderr}"

directory = "/your/directory/path"
print(f"Listing contents of directory: {directory}")
command = ["ls", directory]
output = execute_command(" ".join(command))
print(output)

# Example usage with multiple directories
directories = ["/path/to/dir1", "/path/to/dir2"]
for dir in directories:
    print(f"\nListing contents of directory: {dir}")
    command = ["ls", dir]
    output = execute_command(" ".join(command))
    print(output)