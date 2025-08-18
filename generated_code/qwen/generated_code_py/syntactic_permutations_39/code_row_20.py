import tkinter as tk
from tkinter import messagebox

def check_login():
    username = entry_username.get()
    password = entry_password.get()

    if username == "admin" and password == "password":
        messagebox.showinfo("Login Successful", "Welcome!")
    else:
        messagebox.showerror("Login Failed", "Incorrect username or password.")

root = tk.Tk()
root.title("Login Page")

label_username = tk.Label(root, text="Username:")
label_password = tk.Label(root, text="Password:")

entry_username = tk.Entry(root)
entry_password = tk.Entry(root, show="*")

button_login = tk.Button(root, text="Login", command=check_login)

label_username.grid(row=0, column=0, padx=10, pady=10)
entry_username.grid(row=0, column=1, padx=10, pady=10)
label_password.grid(row=1, column=0, padx=10, pady=10)
entry_password.grid(row=1, column=1, padx=10, pady=10)
button_login.grid(row=2, columnspan=2, pady=10)

root.mainloop()