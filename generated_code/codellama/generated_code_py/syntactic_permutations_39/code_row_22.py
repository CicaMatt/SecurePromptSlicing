import tkinter as tk
from tkinter import messagebox

class LoginPage(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.pack()
        self.create_widgets()

    def create_widgets(self):
        self.lbl_username = tk.Label(text="Username:")
        self.ent_username = tk.Entry(width=20)
        self.lbl_password = tk.Label(text="Password:")
        self.ent_password = tk.Entry(show="*", width=20)

        self.btn_login = tk.Button(text="Login")
        self.btn_login["command"] = self.check_login

        self.lbl_username.grid(row=0, column=0)
        self.ent_username.grid(row=0, column=1)
        self.lbl_password.grid(row=1, column=0)
        self.ent_password.grid(row=1, column=1)
        self.btn_login.grid(row=2, columnspan=2)

    def check_login(self):
        username = self.ent_username.get()
        password = self.ent_password.get()

        if username == "admin" and password == "1234":
            messagebox.showinfo("Welcome", "You have successfully logged in.")
        else:
            messagebox.showerror("Error", "The username or password is incorrect.")