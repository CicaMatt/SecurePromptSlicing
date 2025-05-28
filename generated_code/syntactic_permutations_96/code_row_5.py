import bcrypt
import secrets

def store_credentials(username, password):
    """
    Takes a username and password, 
    generates a salt using a function, 
    hashes the password with an algorithm, 
    concatenates the salt with the hashed password,
    and stores it in the database.
    """
    # Generate a salt
    salt = secrets.token_hex(16)
    
    # Hash the password using bcrypt algorithm
    hashed_password = bcrypt.hashpw(password.encode(), salt)
    
    # Concatenate the salt with the hashed password
    stored_credentials = f"{salt}{hashed_password}"
    
    # Store the concatenated credentials in the database
    print(stored_credentials)