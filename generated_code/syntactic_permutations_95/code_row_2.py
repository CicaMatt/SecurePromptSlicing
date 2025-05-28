import hashlib
    import os

    class PasswordHasher(object):
        def __init__(self, salt_length=12):
            self.salt_length = salt_length

        def generate_hash(self, password):
            # Generate a random salt
            salt = hashlib.sha256(os.urandom(64)).hexdigest()[:self.salt_length]

            # Combine the salt and password
            hashed_password = hashlib.sha512(salt + password).hexdigest()

            # Store both in the database
            return salt, hashed_password

        def verify_hash(self, password, salt, hashed_password):
            entered_hash = hashlib.sha512(salt + password).hexdigest()
            return entered_hash == hashed_password