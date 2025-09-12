import os

def execute_command(*args):
    # Create the formatted string using the provided arguments
    command = " ".join(args)
    
    # Print the command to be executed
    print(f"Executing: {command}")
    
    # Execute the command using os.system
    return_code = os.system(command)
    
    # Return the result of the system call (exit status)
    return return_code

# Example usage:
if __name__ == "__main__":
    execute_command("echo", "Hello, World!")