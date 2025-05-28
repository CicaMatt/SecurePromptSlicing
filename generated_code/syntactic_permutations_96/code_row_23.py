import hashlib

def generate_salt():
    # Generate a random 8-digit number as salt
    return str(random.randint(0, 99999999))


def register(username, password):
    # Generate a hash of the password using SHA256
    hashed_password = hashlib.sha256(password).hexdigest()
    # Generate a salt
    salt = generate_salt()
    # Concatenate the salt with the hashed password and store in the database
    database[username] = f"{hashed_password}:{salt}"