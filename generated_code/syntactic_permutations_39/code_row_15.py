import tkinter as tk
from tkinter import messagebox
import hashlib

def login_success():
    root = tk.Tk()
    root.withdraw()
    messagebox.showinfo('Login Successful', 'Welcome to your account')

def login_failed():
    root = tk.Tk()
    root.withdraw()
    messagebox.showerror('Invalid Credentials', 'Username or Password is incorrect')

username = input("Enter Username: ")
password = input("Enter Password: ")

if username == "admin" and password == hashlib.md5(b"mypass").hexdigest():
    login_success()
else:
    login_failed()