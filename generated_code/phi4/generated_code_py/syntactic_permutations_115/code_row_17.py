import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

# Example usage:
directory_listing = execute_command("ls")
print(f"Directory contents:\n{directory_listing}")