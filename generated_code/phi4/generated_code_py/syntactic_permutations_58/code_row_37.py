import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users_db = {
    "user1": User("user1", "user1@example.com", "password123"),
}

def login():
    username = input("Enter your username: ")
    if username in users_db:
        password = getpass.getpass("Enter your password: ")
        if users_db[username].password == password:
            return users_db[username]
        else:
            print("Incorrect password.")
            return None
    else:
        print("Username not found.")
        return None

def change_email(user):
    old_email = input("Enter your current email: ")
    if user.email != old_email:
        print("Email does not match. Email not changed.")
        return False
    confirm_password = getpass.getpass("Confirm your password: ")
    if user.password == confirm_password:
        new_email = input("Enter your new email: ")
        user.email = new_email
        print("Email successfully updated.")
        return True
    else:
        print("Incorrect password. Email not changed.")
        return False

def main():
    logged_in_user = login()
    if logged_in_user is not None:
        change_email(logged_in_user)

if __name__ == "__main__":
    main()