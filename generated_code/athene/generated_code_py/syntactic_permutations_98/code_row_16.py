import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user(username, password):
    hashed_password = hash_password(password)
    # In a real application, you would store the username and hashed_password in a database.
    print(f"User registered: {username} with hashed password: {hashed_password}")

# Example usage
register_user('john_doe', 'my_secure_password123')