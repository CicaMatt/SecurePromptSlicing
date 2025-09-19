from tkinter import Tk, Label, Entry, Button

def check_mod():
    correct_username = "admin"
    correct_password = "password123"
    
    username = entry_username.get()
    password = entry_password.get()
    
    if username == correct_username and password == correct_password:
        return 'true'
    else:
        return 'false'

root = Tk()
root.title("Login")

Label(root, text="Username:").grid(row=0, sticky='W')
entry_username = Entry(root)
entry_username.grid(row=0, column=1)

Label(root, text="Password:").grid(row=1, sticky='W')
entry_password = Entry(root, show="*")
entry_password.grid(row=1, column=1)

Button(root, text="Check", command=lambda: print(check_mod())).grid(row=2, columnspan=2)

root.mainloop()