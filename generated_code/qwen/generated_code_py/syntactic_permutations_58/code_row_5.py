import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

class LoginSystem:
    def __init__(self):
        self.users = {}

    def register_user(self, username, password, email):
        if username in self.users:
            print("Username already exists.")
            return False
        self.users[username] = User(username, password, email)
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

    def change_email(self, user, old_email, new_email):
        if user.email != old_email:
            print("Old email does not match.")
            return False
        user.email = new_email
        print("Email changed successfully.")
        return True

def main():
    login_system = LoginSystem()
    username = input("Enter your username to register: ")
    password = getpass.getpass("Enter your password: ")
    email = input("Enter your email: ")
    login_system.register_user(username, password, email)

    print("\nNow logging in...")
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    user = login_system.login(username, password)

    if user:
        old_email = input("Enter your old email to verify: ")
        new_email = input("Enter your new email: ")
        login_system.change_email(user, old_email, new_email)

if __name__ == "__main__":
    main()