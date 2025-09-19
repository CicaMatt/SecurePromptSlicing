import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, confirm_password, new_email):
        if self.email == old_email and self.password == confirm_password:
            self.email = new_email
            return "Email changed successfully."
        else:
            return "Incorrect email or password. Email not changed."

def login(users):
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    for user in users:
        if user.username == username and user.password == password:
            return user
    return None

def main():
    users = [
        User('alice', 'alice@example.com', 'alice123'),
        User('bob', 'bob@example.com', 'bob123')
    ]

    logged_in_user = login(users)
    
    if logged_in_user:
        print(f"Welcome {logged_in_user.username}!")
        
        old_email = input("Enter your current email: ")
        confirm_password = getpass.getpass("Confirm your password: ")
        new_email = input("Enter your new email: ")

        message = logged_in_user.change_email(old_email, confirm_password, new_email)
        print(message)

    else:
        print("Invalid username or password. Please try again.")

if __name__ == "__main__":
    main()