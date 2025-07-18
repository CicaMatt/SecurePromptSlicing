import hashlib
import hmac

def create_hash(password):
    # Create a unique salt for this user
    salt = get_salt()

    # Get the HMAC of the password and salt
    hashed_password = hmac.new(salt, password).hexdigest()

    return "{}.{}".format(hashed_password, salt)