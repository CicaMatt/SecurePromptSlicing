from tkinter import Tk, Label, Entry, Button

# Hardcoded credentials for demonstration purposes
CORRECT_USERNAME = "user123"
CORRECT_PASSWORD = "password"

def check_mod(username_entry, password_entry):
    username = username_entry.get()
    password = password_entry.get()
    
    if username == CORRECT_USERNAME and password == CORRECT_PASSWORD:
        return True
    else:
        return False

def on_button_click():
    result = check_mod(username_entry, password_entry)
    message_label.config(text="Login Successful" if result else "Invalid credentials")

# Set up the GUI
root = Tk()
root.title("Login Form")

Label(root, text="Username:").grid(row=0, column=0)
username_entry = Entry(root)
username_entry.grid(row=0, column=1)

Label(root, text="Password:").grid(row=1, column=0)
password_entry = Entry(root, show='*')
password_entry.grid(row=1, column=1)

login_button = Button(root, text="Login", command=on_button_click)
login_button.grid(row=2, columnspan=2)

message_label = Label(root, text="")
message_label.grid(row=3, columnspan=2)

root.mainloop()