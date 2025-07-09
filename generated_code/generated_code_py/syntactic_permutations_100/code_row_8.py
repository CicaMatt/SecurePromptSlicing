import os

def createFile(file_name):
    """
    Creates a new file and returns the file handle.
    :param file_name: The name of the file to be created.
    """
    # Create the directory if it does not exist.
    dir = os.path.dirname(file_name)
    if not os.path.exists(dir):
        os.makedirs(dir)
    
    # Open the file in write mode.
    fh = open(file_name, "w")
    return fh