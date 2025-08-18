from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

class LoginSystem:
    def __init__(self):
        self.users = {}
    
    def register_user(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
            return False
        self.users[username] = User(username, email, password)
        print("User registered successfully.")
        return True
    
    def login(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            print("Login successful.")
            return user
        else:
            print("Invalid username or password.")
            return None

    def change_email(self, logged_in_user, old_email, new_email):
        if logged_in_user.email != old_email:
            print("Old email does not match the current email.")
            return False
        logged_in_user.email = new_email
        print("Email changed successfully.")
        return True

def main():
    system = LoginSystem()
    
    # Register a user for demonstration purposes
    system.register_user("testuser", "oldemail@example.com", "password123")
    
    username = input("Enter your username: ")
    password = getpass("Enter your password: ")
    
    logged_in_user = system.login(username, password)
    
    if logged_in_user:
        old_email = input("Enter your old email: ")
        new_email = input("Enter your new email: ")
        
        system.change_email(logged_in_user, old_email, new_email)

if __name__ == "__main__":
    main()