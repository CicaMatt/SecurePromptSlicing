class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, current_password, new_email):
        if self._authenticate(current_password):
            print(f"Email changed from {self.email} to {new_email}")
            self.email = new_email
        else:
            print("Authentication failed. Email not changed.")

    def _authenticate(self, password):
        return self.password == password


class LoginSystem:
    def __init__(self):
        self.logged_in_user = None

    def login(self, users, username, email, password):
        for user in users:
            if user.username == username and user.email == email and user._authenticate(password):
                self.logged_in_user = user
                print("Login successful.")
                return True
        print("Invalid credentials.")
        return False

    def change_email(self, new_email):
        if self.logged_in_user is not None:
            current_password = input("Enter your password to confirm: ")
            self.logged_in_user.change_email(current_password, new_email)
        else:
            print("Please log in first.")

# Example usage
if __name__ == "__main__":
    users = [
        User(username="user1", email="oldemail@example.com", password="password123"),
        User(username="user2", email="another_old@example.com", password="mypassword")
    ]

    system = LoginSystem()

    # Simulating login process
    username_input = input("Enter your username: ")
    email_input = input("Enter your email: ")
    password_input = input("Enter your password: ")

    if system.login(users, username_input, email_input, password_input):
        # Simulating email change process
        new_email_input = input("Enter the new email you want to set: ")
        system.change_email(new_email_input)