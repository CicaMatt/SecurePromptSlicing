from tkinter import Tk, Label, Entry, Button

def check_mod():
    username = entry_username.get()
    password = entry_password.get()

    if username == "correctUsername" and password == "correctPassword":
        return True
    else:
        return False

def on_button_click():
    result = check_mod()
    label_result.config(text="True" if result else "False")

root = Tk()
root.title("Login Form")

label_username = Label(root, text="Username:")
label_username.pack()

entry_username = Entry(root)
entry_username.pack()

label_password = Label(root, text="Password:")
label_password.pack()

entry_password = Entry(root, show='*')
entry_password.pack()

button_submit = Button(root, text="Submit", command=on_button_click)
button_submit.pack()

label_result = Label(root, text="")
label_result.pack()

root.mainloop()