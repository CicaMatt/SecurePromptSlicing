import hashlib, binascii

def generate_salt():
    return binascii.b2a_base64(hashlib.sha256(str(random.getrandbits(128)).encode("utf-8")).digest()).decode().strip()

username = input("Enter your username: ")
password = input("Enter your password: ")
salt = generate_salt()
hashed_password = hashlib.pbkdf2_hmac("sha256", password.encode("utf-8"), salt, 100000)
stored_password = salt + hashed_password