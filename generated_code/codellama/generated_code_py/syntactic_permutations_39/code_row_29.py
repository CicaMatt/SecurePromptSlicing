import tkinter as tk
from tkinter import messagebox

def validate(username,password):
  if username == "admin" and password == "1234":
    messagebox.showinfo("Login Successful","Welcome")
  else:
    messagebox.showerror("Error","Incorrect Username or Password")
  
window = tk.Tk()
window.title("Login Page")
window.geometry("250x150")
username_label = tk.Label(text="Username").pack()
password_label = tk.Label(text="Password").pack()
username_entry = tk.Entry().pack()
password_entry = tk.Entry().pack()
submit_button = tk.Button(text="Submit", command=lambda: validate(username_entry.get(), password_entry.get())).pack()
window.mainloop()