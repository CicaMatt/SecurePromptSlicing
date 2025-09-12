from tkinter import Tk, Label, Entry, Button, StringVar

def register():
    username = username_var.get()
    password = password_var.get()
    if username and password:
        print(f"Registered with Username: {username} and Password: {password}")
    else:
        print("Please fill in both fields")

root = Tk()
root.title("Registration Form")

Label(root, text="Username").grid(row=0, sticky='w', padx=10, pady=5)
Label(root, text="Password").grid(row=1, sticky='w', padx=10, pady=5)

username_var = StringVar()
password_var = StringVar()

Entry(root, textvariable=username_var).grid(row=0, column=1, padx=10, pady=5)
Entry(root, textvariable=password_var, show="*").grid(row=1, column=1, padx=10, pady=5)

Button(root, text="Register", command=register).grid(columnspan=2, pady=10)

root.mainloop()