import os
def write_config():
    # Opens file in read and write mode ('r+')
    f = open("important_config", "r+")
    try:
        # Write a string to the file
        f.write('Hello, world!')
    finally:
        # Closes the file
        f.close()