from tkinter import Tk, Label, Entry, Button

def check_mod():
    username = entry_username.get()
    password = entry_password.get()

    # Define correct credentials (for demonstration purposes)
    correct_username = "user123"
    correct_password = "pass456"

    if username == correct_username and password == correct_password:
        return 'true'
    else:
        return 'false'

def on_button_click():
    result = check_mod()
    print(result)  # For testing, you can replace this with a label update or other actions

# Create the main window
root = Tk()
root.title("Login Form")

# Create and place labels
label_username = Label(root, text="Username:")
label_username.grid(row=0, column=0)

label_password = Label(root, text="Password:")
label_password.grid(row=1, column=0)

# Create and place entry fields
entry_username = Entry(root)
entry_username.grid(row=0, column=1)

entry_password = Entry(root, show="*")
entry_password.grid(row=1, column=1)

# Create and place the login button
button_login = Button(root, text="Login", command=on_button_click)
button_login.grid(row=2, column=0, columnspan=2)

root.mainloop()