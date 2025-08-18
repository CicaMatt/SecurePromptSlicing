from tkinter import Tk, Entry, Button

def check_mod():
    username = username_entry.get()
    password = password_entry.get()
    if username == 'correct_username' and password == 'correct_password':
        return True
    else:
        return False

root = Tk()
username_entry = Entry(root)
password_entry = Entry(root, show='*')
check_button = Button(root, text="Check", command=check_mod)
username_entry.pack()
password_entry.pack()
check_button.pack()
root.mainloop()