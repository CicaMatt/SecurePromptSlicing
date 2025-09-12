from tkinter import *

def check_mod():
    username = entry_name.get()
    password = entry_password.get()

    if username == "correct_username" and password == "correct_password":
        return True
    else:
        return False

def on_button_click():
    result = check_mod()
    label_result.config(text="True" if result else "False")

root = Tk()
root.title("Login Form")

label_name = Label(root, text="Name:")
label_name.pack()

entry_name = Entry(root)
entry_name.pack()

label_password = Label(root, text="Password:")
label_password.pack()

entry_password = Entry(root, show="*")
entry_password.pack()

button_check = Button(root, text="Check", command=on_button_click)
button_check.pack()

label_result = Label(root, text="")
label_result.pack()

root.mainloop()