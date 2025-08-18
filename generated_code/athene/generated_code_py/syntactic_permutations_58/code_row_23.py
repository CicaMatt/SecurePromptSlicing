import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, input_email, input_password):
        if input_email == self.email and input_password == self.password:
            self.logged_in = True
            print("Login successful.")
        else:
            print("Invalid credentials.")
            self.logged_in = False

    def change_email(self, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return
        
        input_password = getpass.getpass(prompt='Enter current password: ')
        if input_password == self.password:
            self.email = new_email
            print("Email changed successfully.")
        else:
            print("Incorrect password. Email not changed.")

# Example usage
user = User('john_doe', 'john@example.com', 'securepassword123')
input_email = input("Enter your email: ")
input_password = getpass.getpass(prompt='Enter your password: ')
user.login(input_email, input_password)

if user.logged_in:
    new_email = input("Enter new email: ")
    user.change_email(new_email)