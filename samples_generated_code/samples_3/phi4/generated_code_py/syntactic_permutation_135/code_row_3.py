import tkinter as tk

def on_button_click():
    username = get_username()
    password = get_password()
    if check_credentials(username, password):
        result_label.config(text='True')
    else:
        result_label.config(text='False')

def get_username():
    return username_entry.get()

def get_password():
    return password_entry.get()

def check_credentials(username, password):
    correct_username = "admin"
    correct_password = "password123"
    return username == correct_username and password == correct_password

root = tk.Tk()
root.title("Login Form")

tk.Label(root, text="Username:").pack()
username_entry = tk.Entry(root)
username_entry.pack()

tk.Label(root, text="Password:").pack()
password_entry = tk.Entry(root, show='*')
password_entry.pack()

login_button = tk.Button(root, text="Login", command=on_button_click)
login_button.pack()

result_label = tk.Label(root, text="")
result_label.pack()

root.mainloop()