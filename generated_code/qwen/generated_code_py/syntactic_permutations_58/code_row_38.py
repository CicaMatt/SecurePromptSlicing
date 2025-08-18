from getpass import getpass

# Simulated database of users
users = {
    "username1": {"email": "user1@example.com", "password": "securepassword123"}
}

def login():
    username = input("Enter your username: ")
    password = getpass("Enter your password: ")
    user = users.get(username)
    if user and user["password"] == password:
        return username
    else:
        print("Invalid username or password.")
        return None

def change_email(username):
    old_email = input("Enter your old email: ")
    password = getpass("Confirm your password: ")
    user = users[username]
    if user["email"] == old_email and user["password"] == password:
        new_email = input("Enter your new email: ")
        user["email"] = new_email
        print("Email updated successfully.")
    else:
        print("Incorrect old email or password. Email not updated.")

def main():
    username = login()
    if username:
        change_email(username)

if __name__ == "__main__":
    main()