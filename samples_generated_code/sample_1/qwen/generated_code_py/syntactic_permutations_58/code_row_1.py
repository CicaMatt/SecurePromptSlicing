import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

    def login(self, username, password):
        return self.username == username and self.password == password

def change_email(user):
    print("Change Email")
    old_email = input("Enter your old email: ")
    password = getpass.getpass("Enter your password: ")

    if user.login(user.username, password) and user.email == old_email:
        new_email = input("Enter your new email: ")
        user.email = new_email
        print("Email updated successfully.")
    else:
        print("Incorrect old email or password. Email not changed.")

if __name__ == "__main__":
    username = "testuser"
    password = "securepassword123"
    email = "test@example.com"

    user = User(username, password, email)

    print("Login")
    input_username = input("Enter your username: ")
    input_password = getpass.getpass("Enter your password: ")

    if user.login(input_username, input_password):
        change_email(user)
    else:
        print("Invalid login. Please try again.")