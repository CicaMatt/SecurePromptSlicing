import hashlib
import binascii

def register(username, password):
    # Hash the password so it's not stored as plaintext.
    password_hash = hashlib.sha256()
    password_hash.update(password)
    digest = password_hash.hexdigest()

    # Store the username and digest in a database.
    db = {}
    db[username] = digest

register("myuser", "mypass")