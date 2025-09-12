import tkinter as tk
from tkinter import messagebox

def register():
    name = entry_name.get()
    email = entry_email.get()
    password = entry_password.get()
    if not (name and email and password):
        messagebox.showwarning("Input Error", "All fields are required")
    else:
        messagebox.showinfo("Success", f"Registration successful!\nName: {name}\nEmail: {email}")

root = tk.Tk()
root.title("Registration Form")

label_name = tk.Label(root, text="Name:")
label_name.grid(row=0, column=0)
entry_name = tk.Entry(root)
entry_name.grid(row=0, column=1)

label_email = tk.Label(root, text="Email:")
label_email.grid(row=1, column=0)
entry_email = tk.Entry(root)
entry_email.grid(row=1, column=1)

label_password = tk.Label(root, text="Password:")
label_password.grid(row=2, column=0)
entry_password = tk.Entry(root, show="*")
entry_password.grid(row=2, column=1)

register_button = tk.Button(root, text="Register", command=register)
register_button.grid(row=3, columnspan=2)

root.mainloop()