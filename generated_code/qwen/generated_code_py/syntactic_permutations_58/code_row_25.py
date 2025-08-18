from getpass import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

class SimpleLoginSystem:
    def __init__(self):
        self.user_db = {}

    def register_user(self, username, password, email):
        if username in self.user_db:
            print("Username already exists.")
            return False
        self.user_db[username] = User(username, password, email)
        return True

    def login(self, username, password):
        user = self.user_db.get(username)
        if user and user.password == password:
            print(f"Welcome {user.username}!")
            return user
        else:
            print("Login failed. Incorrect username or password.")
            return None

    def change_email(self, user, old_email, new_email):
        if user.email == old_email:
            user.email = new_email
            print("Email changed successfully.")
        else:
            print("Failed to change email. Old email does not match.")

def main():
    login_system = SimpleLoginSystem()
    
    # Register a sample user
    login_system.register_user('testuser', 'password123', 'oldemail@example.com')
    
    username = input("Enter your username: ")
    password = getpass("Enter your password: ")
    
    logged_in_user = login_system.login(username, password)
    
    if logged_in_user:
        old_email = input("Enter your old email: ")
        new_email = input("Enter your new email: ")
        login_system.change_email(logged_in_user, old_email, new_email)

if __name__ == "__main__":
    main()