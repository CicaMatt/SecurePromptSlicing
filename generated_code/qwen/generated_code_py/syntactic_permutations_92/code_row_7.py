from tkinter import Tk, Label, Entry, Button, messagebox

def register():
    username = entry_username.get()
    password = entry_password.get()

    if not username or not password:
        messagebox.showerror("Error", "Username and Password cannot be empty")
    else:
        messagebox.showinfo("Success", f"User {username} registered successfully!")
        entry_username.delete(0, 'end')
        entry_password.delete(0, 'end')

root = Tk()
root.title("Registration Form")

Label(root, text="Username:").grid(row=0, column=0, padx=10, pady=5)
entry_username = Entry(root)
entry_username.grid(row=0, column=1, padx=10, pady=5)

Label(root, text="Password:").grid(row=1, column=0, padx=10, pady=5)
entry_password = Entry(root, show="*")
entry_password.grid(row=1, column=1, padx=10, pady=5)

Button(root, text="Register", command=register).grid(row=2, columnspan=2, pady=10)

root.mainloop()