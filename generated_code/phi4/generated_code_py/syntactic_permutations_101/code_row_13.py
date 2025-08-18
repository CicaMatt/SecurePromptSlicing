# Open a file in write mode (which will create it if it doesn't exist)
with open('important_config', 'w') as file:
    # Write the specified string to the file
    file.write('is opened')