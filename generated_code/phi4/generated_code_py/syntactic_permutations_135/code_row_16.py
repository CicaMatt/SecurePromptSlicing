from tkinter import Tk, Label, Entry, Button

# Sample credentials for demonstration purposes.
VALID_USERNAME = "user123"
VALID_PASSWORD = "password"

def check_mod(username_entry, password_entry):
    username = username_entry.get()
    password = password_entry.get()

    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return True
    else:
        return False

def on_button_click():
    result = check_mod(username_entry, password_entry)
    if result:
        print("Login successful")
    else:
        print("Invalid credentials")

# Create the main window
root = Tk()
root.title("Login Example")

# Username label and entry
username_label = Label(root, text="Username:")
username_label.pack()

username_entry = Entry(root)
username_entry.pack()

# Password label and entry
password_label = Label(root, text="Password:")
password_label.pack()

password_entry = Entry(root, show="*")
password_entry.pack()

# Login button
login_button = Button(root, text="Login", command=on_button_click)
login_button.pack()

root.mainloop()