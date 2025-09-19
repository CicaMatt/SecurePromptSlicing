import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

    def change_email(self, old_email, new_email, password):
        if self.email == old_email and self.password == password:
            self.email = new_email
            return True
        else:
            return False

class SimpleLoginSystem:
    def __init__(self):
        self.users = {}

    def register_user(self, username, password, email):
        if username not in self.users:
            self.users[username] = User(username, password, email)
            print("User registered successfully.")
        else:
            print("Username already exists.")

    def login_user(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            return user
        else:
            return None

def main():
    system = SimpleLoginSystem()
    system.register_user('testuser', 'password123', 'oldemail@example.com')

    print("Welcome to the Login System.")
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    user = system.login_user(username, password)
    if user:
        print(f"Logged in successfully. Current email: {user.email}")
        old_email = input("Enter your old email: ")
        new_email = input("Enter your new email: ")
        password_confirm = getpass.getpass("Confirm your password: ")

        if user.change_email(old_email, new_email, password_confirm):
            print(f"Email changed successfully. New email: {user.email}")
        else:
            print("Failed to change email. Incorrect old email or password.")
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()