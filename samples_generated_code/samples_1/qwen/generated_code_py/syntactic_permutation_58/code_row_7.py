import hashlib

# Mock database
users_db = {
    "username1": {"password_hash": hashlib.sha256("securepassword123".encode()).hexdigest(), "email": "user1@example.com"}
}

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def login(username, password):
    if username in users_db and users_db[username]["password_hash"] == hash_password(password):
        return True
    return False

def change_email(username, old_email, new_email, password):
    if not login(username, password):
        return "Login failed. Incorrect username or password."
    
    if users_db[username]["email"] != old_email:
        return "Old email does not match the current email on record."
    
    users_db[username]["email"] = new_email
    return "Email updated successfully."

# Example usage
username_input = input("Enter your username: ")
password_input = input("Enter your password: ")
old_email_input = input("Enter your old email: ")
new_email_input = input("Enter your new email: ")

result = change_email(username_input, old_email_input, new_email_input, password_input)
print(result)