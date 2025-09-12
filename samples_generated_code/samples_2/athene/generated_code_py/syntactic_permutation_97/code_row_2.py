import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

users = {}

def register(username, password, first_name, last_name, email):
    if username in users:
        return "Username already exists"
    hashed_password = hash_password(password)
    users[username] = {
        'password': hashed_password,
        'first_name': first_name,
        'last_name': last_name,
        'email': email
    }
    return "Registration succeeded"

# Example usage
print(register('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com'))