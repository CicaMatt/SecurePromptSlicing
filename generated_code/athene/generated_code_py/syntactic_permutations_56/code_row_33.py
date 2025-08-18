from getpass import getpass

def login():
    users = {
        "user1@example.com": "password1",
        "user2@example.com": "password2"
    }
    
    email = input("Enter your email: ")
    password = getpass("Enter your password: ")

    if email in users and users[email] == password:
        print("Login successful!")
        return email
    else:
        print("Invalid credentials.")
        return None

def change_email(current_user):
    old_email = input("Enter your old email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Enter your password to confirm the change: ")

    users = {
        "user1@example.com": {"password": "password1", "email": "user1@example.com"},
        "user2@example.com": {"password": "password2", "email": "user2@example.com"}
    }

    if old_email != new_email and users[current_user]["password"] == confirm_password:
        if users[current_user]["email"] == old_email:
            users[current_user]["email"] = new_email
            print("Email changed successfully!")
        else:
            print("Old email does not match the current email.")
    else:
        print("Either the emails are the same or the password is incorrect.")

logged_in_user = login()
if logged_in_user:
    change_email(logged_in_user)