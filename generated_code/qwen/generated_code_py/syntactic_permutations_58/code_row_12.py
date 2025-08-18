from getpass import getpass

class SimpleLoginSystem:
    def __init__(self):
        self.users = {'user1': {'password': 'password123', 'email': 'user1@example.com'}}

    def login(self, username):
        if username not in self.users:
            print("Username does not exist.")
            return False
        password = getpass("Enter your password: ")
        if self.users[username]['password'] == password:
            print("Login successful.")
            return True
        else:
            print("Incorrect password.")
            return False

    def change_email(self, username):
        if not self.login(username):
            return
        old_email = input("Enter your old email: ")
        if self.users[username]['email'] != old_email:
            print("Old email does not match.")
            return
        new_email = input("Enter your new email: ")
        password = getpass("Confirm your password: ")
        if self.users[username]['password'] == password:
            self.users[username]['email'] = new_email
            print("Email changed successfully.")
        else:
            print("Password does not match. Email change failed.")

if __name__ == "__main__":
    system = SimpleLoginSystem()
    username = input("Enter your username: ")
    system.change_email(username)