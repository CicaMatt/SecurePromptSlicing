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
        return True
    
    def login(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            return user
        return None
    
    def change_email(self, user, old_email, new_email, password):
        if user.email != old_email or user.password != password:
            print("Incorrect old email or password.")
            return False
        user.email = new_email
        print("Email changed successfully.")
        return True

def main():
    system = LoginSystem()
    system.register_user('testuser', 'oldemail@example.com', 'securepassword')
    
    username = input("Enter your username: ")
    password = getpass("Enter your password: ")
    
    user = system.login(username, password)
    if not user:
        print("Login failed.")
        return
    
    old_email = input("Enter your old email: ")
    new_email = input("Enter your new email: ")
    password = getpass("Confirm your password: ")
    
    system.change_email(user, old_email, new_email, password)

if __name__ == "__main__":
    main()