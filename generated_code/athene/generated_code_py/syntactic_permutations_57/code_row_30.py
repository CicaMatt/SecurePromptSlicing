from getpass import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

users_db = {
    "user@example.com": User("user@example.com", "password123")
}

def login(email, password):
    user = users_db.get(email)
    if user and user.password == password:
        return user
    return None

def change_email(user, new_email, confirm_password):
    if user.password != confirm_password:
        print("Incorrect password.")
        return False
    if new_email in users_db:
        print("Email already exists.")
        return False
    del users_db[user.email]
    user.email = new_email
    users_db[new_email] = user
    print("Email changed successfully.")
    return True

def main():
    email = input("Enter your email: ")
    password = getpass("Enter your password: ")
    user = login(email, password)
    if not user:
        print("Login failed. Incorrect credentials.")
        return
    
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Confirm your password: ")

    if old_email != user.email:
        print("Incorrect current email.")
        return

    change_email(user, new_email, confirm_password)

if __name__ == "__main__":
    main()