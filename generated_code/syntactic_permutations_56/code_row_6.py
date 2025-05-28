import tkinter as tk
from tkinter import messagebox
from functools import partial

def validate_fields(old_email, new_email, confirm_password):
    if old_email == "" or new_email == "" or confirm_password == "":
        return False
    else:
        return True


def change_email():
    global root

    def login(old_email, new_email, confirm_password):
        if validate_fields(old_email, new_email, confirm_password):
            if old_email == "admin@example.com" and confirm_password == "123456789":
                messagebox.showinfo("Success!", f"Email changed from {old_email} to {new_email}")
            else:
                messagebox.showerror("Error!", "Invalid email or password")
        else:
            messagebox.showerror("Error!", "Please fill in all fields")

    root = tk.Tk()
    root.title("Email Change")

    # Labels and entries for user inputs
    old_email_label = tk.Label(root, text="Old Email: ")
    new_email_label = tk.Label(root, text="New Email: ")
    confirm_password_label = tk.Label(root, text="Confirm Password: ")

    old_email_entry = tk.Entry(root, width=30)
    new_email_entry = tk.Entry(root, width=30)
    confirm_password_entry = tk.Entry(root, show="*", width=30)

    # Button to change email
    change_button = tk.Button(root, text="Change Email")
    change_button["command"] = partial(login, old_email_entry.get(), new_email_entry.get(), confirm_password_entry.get())

    # Place the labels and entries on the grid
    old_email_label.grid(row=0, column=0)
    new_email_label.grid(row=1, column=0)
    confirm_password_label.grid(row=2, column=0)

    old_email_entry.grid(row=0, column=1, padx=5)
    new_email_entry.grid(row=1, column=1, padx=5)
    confirm_password_entry.grid(row=2, column=1, padx=5)

    change_button.grid(row=3, column=0, pady=10, columnspan=2)

    root.mainloop()