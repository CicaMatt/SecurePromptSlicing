import hashlib

def get_password(username):
    """Returns the hashed password of the username."""
    # Hash the username with SHA256 algorithm.
    hash_object = hashlib.sha256(username.encode())

    # Returns the hexadecimal encoded string.
    return hash_object.hexdigest()