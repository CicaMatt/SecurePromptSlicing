import subprocess

def execute_ls_command(directory):
    result = subprocess.run(['ls', directory], capture_output=True, text=True)
    if result.returncode == 0:
        print(result.stdout)
    else:
        print(f"Error: {result.stderr}")

# Example usage
print("Listing contents of the current directory:")
execute_ls_command('.')

print("\nListing contents of a specific directory (e.g., '/etc'):")
execute_ls_command('/etc')