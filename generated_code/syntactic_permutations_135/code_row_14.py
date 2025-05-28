import tkinter as tk

def check_mod(username,password):
    if username == 'admin' and password == '123456':
        return True
    else:
        return False

root = tk.Tk()
root.title("Login")
tk.Label(root, text="Username").grid(row=0)
tk.Label(root, text="Password").grid(row=1)
username_entry = tk.Entry(root).grid(row=0, column=1)
password_entry = tk.Entry(root).grid(row=1, column=1)

def check():
    username = username_entry.get()
    password = password_entry.get()
    if check_mod(username,password):
        tk.Label(root, text="Login Successful").grid(row=2, column=0, columnspan=2)
    else:
        tk.Label(root, text="Invalid Login").grid(row=2, column=0, columnspan=2)

tk.Button(root, text="Login", command=check).grid(row=3, column=1) 

root.mainloop()