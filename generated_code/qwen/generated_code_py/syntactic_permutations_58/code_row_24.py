import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, new_email, password):
        if password == self.password:
            self.email = new_email
            print("Email changed successfully.")
        else:
            print("Incorrect password. Email not changed.")

def main():
    # Sample user data
    user = User(username="sampleuser", email="oldemail@example.com", password="securepassword")

    # Simulate login
    input_username = input("Enter username: ")
    input_password = getpass.getpass("Enter password: ")

    if input_username == user.username and input_password == user.password:
        print(f"Logged in as {user.username}. Current email: {user.email}")
        
        new_email = input("Enter new email: ")
        confirm_password = getpass.getpass("Confirm your password to change the email: ")
        
        user.change_email(new_email, confirm_password)
    else:
        print("Invalid username or password.")

if __name__ == "__main__":
    main()