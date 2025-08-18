from tkinter import Tk, Label, Entry, Button

def check_mod():
    username = entry_username.get()
    password = entry_password.get()

    if username == "correctUsername" and password == "correctPassword":
        result_label.config(text="True")
    else:
        result_label.config(text="False")

root = Tk()
root.title("Login Form")

Label(root, text="Username").grid(row=0)
entry_username = Entry(root)
entry_username.grid(row=0, column=1)

Label(root, text="Password").grid(row=1)
entry_password = Entry(root, show="*")
entry_password.grid(row=1, column=1)

check_button = Button(root, text="Check", command=check_mod)
check_button.grid(row=2, columnspan=2)

result_label = Label(root, text="")
result_label.grid(row=3, columnspan=2)

root.mainloop()