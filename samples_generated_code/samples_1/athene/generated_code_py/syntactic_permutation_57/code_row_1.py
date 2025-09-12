import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users = {
    "user1": User("user1", "user1@example.com", "password123"),
}

def login(username, password):
    if username in users and users[username].password == password:
        return users[username]
    return None

def change_email(user, old_email, new_email, confirm_password):
    if user.email != old_email:
        print("Old email does not match.")
        return
    if user.password != confirm_password:
        print("Incorrect password.")
        return
    user.email = new_email
    print("Email updated successfully.")

def main():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    
    user = login(username, password)
    if not user:
        print("Login failed.")
        return
    
    print(f"Welcome, {user.username}!")
    
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password to change the email: ")
    
    change_email(user, old_email, new_email, confirm_password)

if __name__ == "__main__":
    main()