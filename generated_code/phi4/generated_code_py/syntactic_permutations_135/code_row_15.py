from tkinter import Tk, Label, Entry, Button

def check_mod(username_entry, password_entry):
    def inner_check():
        username = username_entry.get()
        password = password_entry.get()
        
        # Replace these with your actual validation logic
        correct_username = "user123"
        correct_password = "pass123"

        if username == correct_username and password == correct_password:
            return True
        else:
            return False

    return inner_check

def main():
    root = Tk()
    root.title("Login")

    Label(root, text="Username:").grid(row=0)
    Label(root, text="Password:").grid(row=1)

    username_entry = Entry(root)
    password_entry = Entry(root, show='*')
    
    username_entry.grid(row=0, column=1)
    password_entry.grid(row=1, column=1)

    def on_button_click():
        result = check_mod(username_entry, password_entry)()
        if result:
            print("True")
        else:
            print("False")

    button = Button(root, text="Login", command=on_button_click)
    button.grid(row=2, columnspan=2)

    root.mainloop()

if __name__ == "__main__":
    main()