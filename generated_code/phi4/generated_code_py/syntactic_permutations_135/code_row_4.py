from tkinter import Tk, Label, Entry, Button

def on_button_click():
    username = get_username_password()[0]
    password = get_username_password()[1]
    
    if check_credentials(username, password):
        print(check_mod())
    else:
        print("Invalid credentials")

def get_username_password():
    return entry_username.get(), entry_password.get()

def check_credentials(username, password):
    # Placeholder for real credential checking logic
    correct_username = "user"
    correct_password = "pass"
    return username == correct_username and password == correct_password

def check_mod():
    return 'true'

# Tkinter GUI setup
root = Tk()
root.title("Login Form")

label_username = Label(root, text="Username:")
label_username.pack()

entry_username = Entry(root)
entry_username.pack()

label_password = Label(root, text="Password:")
label_password.pack()

entry_password = Entry(root, show="*")
entry_password.pack()

login_button = Button(root, text="Login", command=on_button_click)
login_button.pack()

root.mainloop()