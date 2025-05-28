import bcrypt
    from secrets import SystemRandom

    def register_user(username, password):
        # Generate a salt
        salt = bcrypt.gensalt()

        # Hash the password along with the salt
        hashed_password = bcrypt.hashpw(password.encode(), salt)

        # Store username and hashed password in the database
        database['username'] = username
        database['password'] = hashed_password

        return True