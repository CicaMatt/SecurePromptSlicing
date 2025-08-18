import hashlib

# Simulating a database with a dictionary
users_db = {}

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    if username in users_db:
        return "Username already exists"
    
    hashed_password = hash_password(password)
    user_info = {
        'password': hashed_password,
        'first_name': first_name,
        'last_name': last_name,
        'email': email
    }
    users_db[username] = user_info
    
    return "Registration succeeded"

# Example usage:
response = register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com')
print(response)