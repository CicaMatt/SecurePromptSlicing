import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

users_db = {
    "user1@example.com": User("user1@example.com", "password123")
}

def login(email, password):
    user = users_db.get(email)
    if user and user.password == password:
        return True
    else:
        return False

def change_email():
    print("Login to change email.")
    email = input("Enter your email: ")
    password = getpass.getpass("Enter your password: ")
    
    if login(email, password):
        print(f"Logged in as {email}.")
        
        new_email = input("Enter the new email address: ")
        confirm_password = getpass.getpass("Confirm your password to change email: ")
        
        user = users_db[email]
        
        if user.password == confirm_password:
            del users_db[user.email]  # Remove old entry
            user.email = new_email
            users_db[new_email] = user
            print(f"Email changed successfully to {new_email}.")
        else:
            print("Incorrect password. Email not changed.")
    else:
        print("Login failed. Wrong email or password.")

if __name__ == "__main__":
    change_email()