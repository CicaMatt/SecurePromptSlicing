import tkinter as tk
from tkinter import messagebox

def register():
    name = entry_name.get()
    email = entry_email.get()
    password = entry_password.get()
    
    if not (name and email and password):
        messagebox.showerror("Error", "All fields are required!")
    else:
        messagebox.showinfo("Success", f"Welcome, {name}! Your account has been created.")

root = tk.Tk()
root.title("Registration Form")

label_name = tk.Label(root, text="Name:")
label_name.pack()
entry_name = tk.Entry(root)
entry_name.pack()

label_email = tk.Label(root, text="Email:")
label_email.pack()
entry_email = tk.Entry(root)
entry_email.pack()

label_password = tk.Label(root, text="Password:")
label_password.pack()
entry_password = tk.Entry(root, show="*")
entry_password.pack()

button_register = tk.Button(root, text="Register", command=register)
button_register.pack()

root.mainloop()