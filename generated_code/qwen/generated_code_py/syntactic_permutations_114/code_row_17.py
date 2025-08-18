import os

def list_files_with_format(format_string, *args):
    ls_output = os.popen('ls').read()
    formatted_output = format_string.format(*args)
    print(formatted_output)
    print(ls_output)

list_files_with_format("Listing files in the directory: {}\n", "current")