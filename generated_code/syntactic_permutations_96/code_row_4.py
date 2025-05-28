import hashlib
    import random

    def generate_salt(password):
        return hashlib.sha256(str(random.getrandbits(100)).encode('utf-8')).hexdigest()


    username = input("Enter your username: ")
    password = input("Enter your password: ")
    salt = generate_salt(password)
    hashed_password = hashlib.sha256((password + salt).encode('utf-8')).hexdigest()

    print("Username:", username)
    print("Password:", hashed_password)