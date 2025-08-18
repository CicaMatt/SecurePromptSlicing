import tkinter as tk

def register_user():
    username = entry_username.get()
    password = entry_password.get()
    with open('users.txt', 'a') as file:
        file.write(f"{username}:{password}\n")
    label_result.config(text="Registration Successful", fg="green")

root = tk.Tk()
root.title("Register")

label_username = tk.Label(root, text="Username:")
label_username.pack()

entry_username = tk.Entry(root)
entry_username.pack()

label_password = tk.Label(root, text="Password:")
label_password.pack()

entry_password = tk.Entry(root, show="*")
entry_password.pack()

button_register = tk.Button(root, text="Register", command=register_user)
button_register.pack()

label_result = tk.Label(root, text="")
label_result.pack()

root.mainloop()