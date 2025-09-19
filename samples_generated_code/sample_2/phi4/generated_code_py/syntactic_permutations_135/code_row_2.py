from tkinter import Tk, Label, Entry, Button

def on_button_click():
    username = get_form_data('username')
    password = get_form_data('password')
    
    if check_mod(username, password):
        print("Access Granted")
    else:
        print("Access Denied")

def get_form_data(field_name):
    return form_fields[field_name].get()

def check_mod(username, password):
    # Simulated correct credentials
    correct_username = "admin"
    correct_password = "password123"

    if username == correct_username and password == correct_password:
        return True
    else:
        return False

# Create main window
root = Tk()
root.title("Login Form")

form_fields = {
    'username': Entry(root),
    'password': Entry(root, show="*")
}

# Place form fields in the window
Label(root, text="Username:").pack()
form_fields['username'].pack()

Label(root, text="Password:").pack()
form_fields['password'].pack()

Button(root, text="Login", command=on_button_click).pack()

root.mainloop()