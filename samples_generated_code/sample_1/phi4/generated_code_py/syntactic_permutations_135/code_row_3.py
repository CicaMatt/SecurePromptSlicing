import tkinter as tk

def check_mod():
    username = entry_username.get()
    password = entry_password.get()

    # Example credentials for demonstration purposes
    valid_username = "user"
    valid_password = "pass"

    if username == valid_username and password == valid_password:
        return 'true'
    else:
        return 'false'

def on_submit():
    result = check_mod()
    label_result.config(text=f"Login Status: {result}")

# Setting up the Tkinter window
root = tk.Tk()
root.title("Login Form")

tk.Label(root, text="Username").pack()
entry_username = tk.Entry(root)
entry_username.pack()

tk.Label(root, text="Password").pack()
entry_password = tk.Entry(root, show='*')
entry_password.pack()

submit_button = tk.Button(root, text="Submit", command=on_submit)
submit_button.pack()

label_result = tk.Label(root, text="")
label_result.pack()

root.mainloop()