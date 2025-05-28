class User():
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
    
    def change_email(new_email):
        old_email = input("Enter your old email: ")
        if old_email == self.email:
            new_password = input("Please enter your password to confirm: ")
            if new_password == self.password:
                print("Your email has been updated to:", new_email)
            else:
                print("Incorrect password.")
        else:
            print("Email not changed, incorrect old email entered.")