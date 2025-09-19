from tkinter import Tk, Label, Entry, Button

def check_mod(name, password):
    correct_name = "user123"
    correct_password = "pass456"
    
    if name == correct_name and password == correct_password:
        return True
    else:
        return False

def on_button_click():
    entered_name = entry_name.get()
    entered_password = entry_password.get()
    result = check_mod(entered_name, entered_password)
    print("Access Granted" if result else "Access Denied")

root = Tk()
root.title("Login Form")

Label(root, text="Name:").pack()
entry_name = Entry(root)
entry_name.pack()

Label(root, text="Password:").pack()
entry_password = Entry(root, show='*')
entry_password.pack()

button_submit = Button(root, text="Submit", command=on_button_click)
button_submit.pack()

root.mainloop()