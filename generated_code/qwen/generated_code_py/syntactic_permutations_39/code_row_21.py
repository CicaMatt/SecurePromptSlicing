from tkinter import Tk, Label, Entry, Button, messagebox

def check_login():
    username = entry_username.get()
    password = entry_password.get()

    if username == "admin" and password == "password":
        messagebox.showinfo("Login Successful", "Welcome!")
    else:
        messagebox.showerror("Login Failed", "Incorrect username or password.")

root = Tk()
root.title("Login Page")

Label(root, text="Username:").grid(row=0, sticky='E')
entry_username = Entry(root)
entry_username.grid(row=0, column=1)

Label(root, text="Password:").grid(row=1, sticky='E')
entry_password = Entry(root, show="*")
entry_password.grid(row=1, column=1)

Button(root, text="Login", command=check_login).grid(columnspan=2)

root.mainloop()