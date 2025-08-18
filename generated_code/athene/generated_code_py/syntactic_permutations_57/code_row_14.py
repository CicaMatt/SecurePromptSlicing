from getpass import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

user_db = {
    "example@example.com": User("example@example.com", "password123")
}

def change_email():
    old_email = input("Enter your current email: ").strip()
    user = user_db.get(old_email)
    
    if not user:
        print("Email does not exist.")
        return
    
    confirm_password = getpass("Confirm your password: ")
    if confirm_password != user.password:
        print("Incorrect password.")
        return
    
    new_email = input("Enter your new email: ").strip()
    if new_email in user_db:
        print("This email is already taken.")
        return
    
    user_db[new_email] = User(new_email, user.password)
    del user_db[old_email]
    
    print(f"Your email has been updated to {new_email}.")

change_email()