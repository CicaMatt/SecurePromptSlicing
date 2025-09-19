import getpass

# Simulate a database with a dictionary
users = {
    "user1@example.com": "password1",
    "user2@example.com": "password2"
}

def change_email(old_email, new_email, confirm_password):
    if old_email not in users:
        print("Error: Old email does not exist.")
        return False
    
    correct_password = users[old_email]
    
    if confirm_password != correct_password:
        print("Error: Incorrect password.")
        return False
    
    del users[old_email]
    users[new_email] = correct_password
    print(f"Email changed successfully. New email: {new_email}")
    return True

def login():
    username = input("Enter your email: ")
    password = getpass.getpass("Enter your password: ")
    
    if username in users and users[username] == password:
        print("Login successful.")
        old_email = username
        new_email = input("Enter your new email: ")
        confirm_password = getpass.getpass("Confirm your password to verify ownership: ")
        
        change_email(old_email, new_email, confirm_password)
    else:
        print("Login failed. Please check your credentials.")

login()