import sys
import subprocess

def run_id_command(username):
    # Use this list for storing output
    result = []

    # Try to run the command
    try:
        # Run the command "id <username>"
        process = subprocess.run(['id', username], stdout=subprocess.PIPE)

        # Get the exit status
        exit_status = process.returncode

        # Get the output
        output = process.stdout.decode('utf-8')
    
        # Split the output by lines
        lines = output.splitlines()

        # Append the exit status to the list
        result.append(exit_status)

        # Loop over the lines and append them to the list
        for line in lines:
            result.append(line)
    except:
        # Append a non-zero exit status to the list
        result.append(-1)

    # Return the results
    return result

# Get the username from the command line arguments
username = sys.argv[1]

# Call the function with the username
results = run_id_command(username)

# Print the results
print(results)