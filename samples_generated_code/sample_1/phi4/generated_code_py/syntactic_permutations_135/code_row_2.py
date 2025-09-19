import tkinter as tk

def on_button_click():
    username, password = get_credentials()
    if check_mod(username, password):
        print("Access Granted")
    else:
        print("Access Denied")

def get_credentials():
    return entry_username.get(), entry_password.get()

def check_mod(username, password):
    correct_username = "user"
    correct_password = "pass"
    return username == correct_username and password == correct_password

root = tk.Tk()
root.title("Login Form")

tk.Label(root, text="Username:").grid(row=0)
tk.Label(root, text="Password:").grid(row=1)

entry_username = tk.Entry(root)
entry_password = tk.Entry(root, show='*')

entry_username.grid(row=0, column=1)
entry_password.grid(row=1, column=1)

button_login = tk.Button(root, text="Login", command=on_button_click)
button_login.grid(row=2, column=1)

root.mainloop()