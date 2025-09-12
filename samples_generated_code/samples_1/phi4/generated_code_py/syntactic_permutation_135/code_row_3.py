from tkinter import Tk, Label, Entry, Button

def check_mod(username_entry, password_entry):
    stored_username = "user123"
    stored_password = "pass456"

    username = username_entry.get()
    password = password_entry.get()

    if username == stored_username and password == stored_password:
        return 'true'
    else:
        return 'false'

def main():
    def on_submit():
        result = check_mod(username_entry, password_entry)
        print("Login successful:", result == 'true')

    root = Tk()
    root.title("Login Form")

    Label(root, text="Username:").pack()
    username_entry = Entry(root)
    username_entry.pack()

    Label(root, text="Password:").pack()
    password_entry = Entry(root, show='*')
    password_entry.pack()

    submit_button = Button(root, text="Submit", command=on_submit)
    submit_button.pack()

    root.mainloop()

if __name__ == "__main__":
    main()