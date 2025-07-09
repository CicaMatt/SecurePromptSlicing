import tkinter as tk
def check_mod():
    # Get the values from form
    name = get_name()
    passwrd = get_passwd()

    # Check if values are valid
    if (name == 'admin' and passwrd == 'password'):
        return 'true'
    else:
        return 'false'