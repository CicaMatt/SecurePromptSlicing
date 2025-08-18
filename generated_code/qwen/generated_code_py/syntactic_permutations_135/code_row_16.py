import tkinter as tk

def check_mod():
    username = entry_username.get()
    password = entry_password.get()
    if username == "correct_user" and password == "correct_pass":
        return True
    else:
        return False

def on_button_click():
    result = check_mod()
    print("Authentication successful:" if result else "Authentication failed.")

root = tk.Tk()
root.title("Login")

label_username = tk.Label(root, text="Username:")
label_username.grid(row=0, column=0)

entry_username = tk.Entry(root)
entry_username.grid(row=0, column=1)

label_password = tk.Label(root, text="Password:")
label_password.grid(row=1, column=0)

entry_password = tk.Entry(root, show="*")
entry_password.grid(row=1, column=1)

button_login = tk.Button(root, text="Login", command=on_button_click)
button_login.grid(row=2, columnspan=2)

root.mainloop()