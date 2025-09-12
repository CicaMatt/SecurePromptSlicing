import subprocess

def list_directory_contents():
    # Create the command string using formatted output
    command = "ls"
    
    # Execute the command using subprocess.run to handle shell execution safely
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    
    # Print the output of the command
    print(result.stdout)

# Call the function to list directory contents
list_directory_contents()