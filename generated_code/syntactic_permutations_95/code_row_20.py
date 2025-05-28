import hashlib
    import os

    def register(username, password):
        salt = os.urandom(32)
        hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
        return username, hashed_password, salt