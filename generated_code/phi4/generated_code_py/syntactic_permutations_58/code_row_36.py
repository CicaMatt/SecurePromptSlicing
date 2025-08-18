import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users_db = {
    "user1": User("user1", "user1@example.com", "password123")
}

def login(username):
    user = users_db.get(username)
    if not user:
        return None
    print(f"Logged in as {username}.")
    return user

def change_email(user, old_email, new_email):
    if user.email == old_email and getpass.getpass(prompt="Enter your password: ") == user.password:
        user.email = new_email
        print("Email changed successfully.")
    else:
        print("Old email or password is incorrect. Email not changed.")

def main():
    username_input = input("Enter your username to login: ")
    user = login(username_input)
    
    if user:
        old_email_input = input(f"Your current email is {user.email}. Enter the old email you want to change from: ")
        new_email_input = input("Enter the new email: ")
        change_email(user, old_email_input, new_email_input)

if __name__ == "__main__":
    main()