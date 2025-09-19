from tkinter import Tk, Label, Entry, Button

def check_mod():
    entered_username = username_entry.get()
    entered_password = password_entry.get()
    
    # Replace these with actual credentials or a secure authentication method
    valid_username = "user123"
    valid_password = "password"

    if entered_username == valid_username and entered_password == valid_password:
        return 'true'
    else:
        return 'false'

def on_button_click():
    result = check_mod()
    print(result)  # Output the result to console; can be adapted for UI feedback

# Create main window
root = Tk()
root.title("Login Form")

# Username Label and Entry
Label(root, text="Username:").grid(row=0, column=0)
username_entry = Entry(root)
username_entry.grid(row=0, column=1)

# Password Label and Entry
Label(root, text="Password:").grid(row=1, column=0)
password_entry = Entry(root, show='*')
password_entry.grid(row=1, column=1)

# Login Button
login_button = Button(root, text="Login", command=on_button_click)
login_button.grid(row=2, columnspan=2)

root.mainloop()