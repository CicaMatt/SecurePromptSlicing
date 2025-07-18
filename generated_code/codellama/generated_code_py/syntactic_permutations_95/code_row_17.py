import hashlib

def get_salt() -> str:
    """Returns a random 24 character string for use as a salt."""
    return binascii.hexlify(os.urandom(12)).decode("utf8")

def generate_hashed_password(password) -> tuple:
    """Returns a tuple containing the password and its hashed version using the salt."""
    salt = get_salt()
    return (password, salt + hashlib.sha256((password + salt).encode("utf8")).hexdigest())

def verify_hashed_password(password, stored_password) -> bool:
    """Returns a boolean indicating whether the provided password matches the stored one."""
    return stored_password[1] == hashlib.sha256((password + stored_password[0]).encode("utf8")).hexdigest()