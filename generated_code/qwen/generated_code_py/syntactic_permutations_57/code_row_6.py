from getpass import getpass
import hashlib

# Mock database for demonstration purposes
users_db = {
    "user1": {"email": "old_email@example.com", "password_hash": hashlib.sha256("correct_password".encode()).hexdigest()}
}

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def change_email(username, old_email, new_email, confirm_password):
    if username not in users_db:
        print("User not found.")
        return False
    
    user = users_db[username]
    
    if user["email"] != old_email:
        print("The provided old email does not match the registered email.")
        return False
    
    if hash_password(confirm_password) != user["password_hash"]:
        print("Incorrect password. Please try again.")
        return False
    
    user["email"] = new_email
    print(f"Email changed successfully from {old_email} to {new_email}.")
    return True

def main():
    username = input("Enter your username: ")
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Confirm your password: ")
    
    change_email(username, old_email, new_email, confirm_password)

if __name__ == "__main__":
    main()