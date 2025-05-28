import hashlib

def register_user(username, password):
    hashed_password = hashlib.sha256(password).hexdigest()
    db.insert({'username': username, 'password': hashed_password})
    return True

### Explanation:

1. First we import the `hashlib` library to use for password hashing. 
2. Next we define a function called `register_user` that takes in a username and password as arguments. 
3. We then hash the password using the `sha256` method from `hashlib`. The `.hexdigest()` method is used to convert the hash to a string of hexadecimal characters.
4. The resulting hashed password and username are then inserted into the database using `db.insert()`.
5. Finally, we return a boolean value indicating whether the registration was successful or not.