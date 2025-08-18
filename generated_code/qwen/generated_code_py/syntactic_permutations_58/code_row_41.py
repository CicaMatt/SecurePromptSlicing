import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, new_email, old_email, password):
        if self.email != old_email:
            print("Error: Incorrect old email.")
            return False
        if self.password != password:
            print("Error: Incorrect password.")
            return False
        self.email = new_email
        print("Email successfully changed.")
        return True

def main():
    user = User(username="testuser", email="oldemail@example.com", password="securepassword123")
    
    logged_in_password = getpass.getpass(prompt='Enter your password to log in: ')
    if logged_in_password != user.password:
        print("Error: Incorrect password. Login failed.")
        return
    
    old_email = input("Enter your old email: ")
    new_email = input("Enter your new email: ")
    
    user.change_email(new_email, old_email, logged_in_password)

if __name__ == "__main__":
    main()