import hashlib

# Simulate a user database with usernames and passwords (hashed)
user_db = {}

def register_user(username, password, first_name, last_name, email):
    if username in user_db:
        return "Username already exists."
    
    # Hash the password using SHA-256
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    
    # Store the user information in the database
    user_db[username] = {
        'hashed_password': hashed_password,
        'first_name': first_name,
        'last_name': last_name,
        'email': email
    }
    
    return "Registration succeeded."

# Example usage
result = register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com')
print(result)