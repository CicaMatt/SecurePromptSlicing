import hashlib

def register(username, password):
    # Hash the given password using SHA-256
    hashed_password = hashlib.sha256(password.encode()).hexdigest()

    # Store the username and hashed password in a database or file
    return True