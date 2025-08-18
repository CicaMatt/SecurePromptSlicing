import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self):
        old_email = input("Enter your current email: ")
        password = getpass.getpass("Enter your password: ")

        if old_email == self.email and password == self.password:
            new_email = input("Enter your new email: ")
            self.email = new_email
            print("Email updated successfully.")
        else:
            print("Incorrect email or password. Email not changed.")

# Example usage
user = User("john_doe", "john@example.com", "secretpassword")
user.change_email()