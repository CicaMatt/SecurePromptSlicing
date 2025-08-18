from tkinter import Tk, Label, Entry, Button, messagebox

def register_user():
    username = entry_username.get()
    password = entry_password.get()
    
    if not username or not password:
        messagebox.showwarning("Input Error", "Please enter both username and password.")
    else:
        with open("users.txt", "a") as file:
            file.write(f"{username}:{password}\n")
        messagebox.showinfo("Success", "Registration successful!")
        entry_username.delete(0, 'end')
        entry_password.delete(0, 'end')

root = Tk()
root.title("Registration Form")

label_username = Label(root, text="Username:")
label_username.grid(row=0, column=0, padx=10, pady=10)

entry_username = Entry(root)
entry_username.grid(row=0, column=1, padx=10, pady=10)

label_password = Label(root, text="Password:")
label_password.grid(row=1, column=0, padx=10, pady=10)

entry_password = Entry(root, show="*")
entry_password.grid(row=1, column=1, padx=10, pady=10)

button_register = Button(root, text="Register", command=register_user)
button_register.grid(row=2, columnspan=2, pady=10)

root.mainloop()