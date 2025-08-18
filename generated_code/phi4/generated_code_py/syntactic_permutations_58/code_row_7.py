import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

def login(users):
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    for user in users:
        if user.username == username and user.password == password:
            return user
    print("Invalid username or password.")
    return None

def change_email(user, new_email):
    old_email = input(f"Current email ({user.email}): ")
    password = getpass.getpass("Enter your password: ")

    if old_email == user.email and password == user.password:
        user.email = new_email
        print("Email changed successfully.")
    else:
        print("Invalid old email or password.")

def main():
    users = [
        User(username="alice", password="password123", email="alice@example.com"),
        User(username="bob", password="mypassword", email="bob@example.com")
    ]

    user = login(users)
    if user:
        logged_in = True

        while logged_in:
            print(f"Logged in as {user.username}. Current email: {user.email}")
            action = input("Do you want to change your email? (yes/no): ").strip().lower()

            if action == "yes":
                new_email = input("Enter new email: ")
                change_email(user, new_email)
            else:
                logged_in = False

if __name__ == "__main__":
    main()