from tkinter import Tk, Label, Entry, Button, messagebox

def register():
    username = entry_username.get()
    password = entry_password.get()
    
    if not username or not password:
        messagebox.showerror("Error", "Username and Password cannot be empty")
        return
    
    with open('users.txt', 'a') as file:
        file.write(f"{username}:{password}\n")
        
    messagebox.showinfo("Success", "Registration successful!")
    entry_username.delete(0, 'end')
    entry_password.delete(0, 'end')

def clear_form():
    entry_username.delete(0, 'end')
    entry_password.delete(0, 'end')

app = Tk()
app.title("Registration Form")
app.geometry('300x150')

Label(app, text="Username:").pack(pady=5)
entry_username = Entry(app)
entry_username.pack(pady=5)

Label(app, text="Password:").pack(pady=5)
entry_password = Entry(app, show='*')
entry_password.pack(pady=5)

Button(app, text="Register", command=register).pack(pady=5)
Button(app, text="Clear", command=clear_form).pack(pady=5)

app.mainloop()