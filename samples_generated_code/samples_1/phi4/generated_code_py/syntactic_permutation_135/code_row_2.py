from tkinter import Tk, Label, Entry, Button

def on_button_click():
    username = get_credentials()
    password = get_credentials(password=True)
    if check_login(username, password):
        print("Login successful")
    else:
        print("Login failed")

def get_credentials(password=False):
    return credentials_entry.get() if not password else password_entry.get()

def check_login(username, password):
    return check_mod(username, password) == 'true'

def check_mod(username, password):
    # Replace these with actual checks
    valid_username = "admin"
    valid_password = "password123"
    if username == valid_username and password == valid_password:
        return 'true'
    else:
        return 'false'

root = Tk()
root.title("Login Form")

Label(root, text="Username:").pack()
credentials_entry = Entry(root)
credentials_entry.pack()

Label(root, text="Password:").pack()
password_entry = Entry(root, show='*')
password_entry.pack()

login_button = Button(root, text="Login", command=on_button_click)
login_button.pack()

root.mainloop()