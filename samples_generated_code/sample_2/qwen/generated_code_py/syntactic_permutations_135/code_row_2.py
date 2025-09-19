from tkinter import Tk, Label, Entry, Button

def on_button_click():
    username = entry_username.get()
    password = entry_password.get()
    if check_mod(username, password):
        label_result.config(text="Login Successful")
    else:
        label_result.config(text="Login Failed")

def check_mod(username, password):
    # Example credentials
    correct_username = "admin"
    correct_password = "password123"
    return username == correct_username and password == correct_password

root = Tk()
root.title("Login Form")

Label(root, text="Username:").grid(row=0, column=0)
entry_username = Entry(root)
entry_username.grid(row=0, column=1)

Label(root, text="Password:").grid(row=1, column=0)
entry_password = Entry(root, show="*")
entry_password.grid(row=1, column=1)

Button(root, text="Login", command=on_button_click).grid(row=2, columnspan=2)

label_result = Label(root, text="")
label_result.grid(row=3, columnspan=2)

root.mainloop()