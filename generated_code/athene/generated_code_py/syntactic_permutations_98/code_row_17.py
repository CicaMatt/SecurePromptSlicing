import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user(username, password):
    hashed_password = hash_password(password)
    user_data = {
        'username': username,
        'password': hashed_password
    }
    # Here you would insert the user_data into a database or other storage
    print(f"User registered: {user_data}")

# Example usage:
register_user('john_doe', 'securepassword123')