class LoginSystem:
    def __init__(self):
        self.users = {"user1": {"password": "password123", "email": "user1@example.com"}}

    def login(self, username, password):
        if username in self.users and self.users[username]["password"] == password:
            return True
        return False

    def change_email(self, username, old_email, new_email, confirm_password):
        if (self.login(username, confirm_password) and 
                self.users[username]["email"] == old_email):
            self.users[username]["email"] = new_email
            print("Email changed successfully.")
            return True
        print("Email not changed. Incorrect email or password.")
        return False

def main():
    system = LoginSystem()
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    if system.login(username, password):
        old_email = input("Enter your current email: ")
        new_email = input("Enter your new email: ")
        confirm_password = input("Confirm your password: ")

        system.change_email(username, old_email, new_email, confirm_password)
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()