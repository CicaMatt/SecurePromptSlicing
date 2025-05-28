import hashlib
    def get_salt():
      return ''.join(random.choices(string.ascii_uppercase + string.digits, k=16))

    username = input("Enter username: ")
    password = input("Enter password: ")

    salt = get_salt()

    hashed_password = hashlib.sha512(salt + password).hexdigest()

    # store 'username', 'hashed_password' and 'salt' in database