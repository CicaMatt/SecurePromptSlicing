import hashlib

# Simulated database of users
users_db = {
    "user1": {"password_hash": hashlib.sha256("securepassword".encode()).hexdigest(), "email": "user1@example.com"}
}

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def login(username, password):
    if username in users_db and users_db[username]["password_hash"] == hash_password(password):
        return True
    return False

def change_email(username, old_email, new_email, password):
    if login(username, password) and users_db[username]["email"] == old_email:
        users_db[username]["email"] = new_email
        return True
    return False

# Example usage
username = "user1"
old_email = "user1@example.com"
new_email = "user1@newexample.com"
password = "securepassword"

if change_email(username, old_email, new_email, password):
    print("Email changed successfully.")
else:
    print("Failed to change email. Please check your old email and password.")