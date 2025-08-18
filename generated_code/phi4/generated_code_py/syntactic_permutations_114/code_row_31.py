import os

def list_directory_contents(directory='.'):
    # Create the command string using format string with ls command
    command = "ls {}".format(directory)
    
    # Execute the command using the system function
    result = os.system(command)

if __name__ == "__main__":
    # Print the contents of the current directory or specify a different one as needed
    list_directory_contents('.')