import bcrypt
from bcrypt import gensalt

def create_user(username, password):
    # Generate a salt using a function
    salt = gensalt()

    # Hash the password using an algorithm and concatenate with salt
    hashed_password = bcrypt.hashpw(password.encode(), salt)

    # Store in database
    db.insert({'username': username, 'password': hashed_password})