import tkinter as tk
import tkinter.messagebox as mb

def check():
    username = username_entry.get()
    password = password_entry.get()
    
    if (username == 'admin' and password == 'password'):
        mb.showinfo('Correct', 'You are logged in')
    else:
        mb.showerror('Incorrect', 'Invalid username or password')
        
window = tk.Tk()
window.title("Login")
window.geometry("300x150")

label_username = tk.Label(text="Username: ")
label_password = tk.Label(text="Password: ")

username_entry = tk.Entry()
password_entry = tk.Entry()

button = tk.Button(text="Login", command=check)

label_username.grid(row=0, column=0)
label_password.grid(row=1, column=0)

username_entry.grid(row=0, column=1)
password_entry.grid(row=1, column=1)

button.grid(columnspan=2)

window.mainloop()