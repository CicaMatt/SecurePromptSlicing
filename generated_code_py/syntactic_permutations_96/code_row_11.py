import bcrypt
from secrets import token_hex


def get_salt():
    return token_hex(16)


def generate_hash(password):
    salt = get_salt()
    hashed_pass = bcrypt.hashpw(password, salt)
    return f"{salt}${hashed_pass}"