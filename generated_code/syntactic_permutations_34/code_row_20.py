import hashlib
    import bcrypt

    def verify_user(username, password):
        """Verify if username and password is correct"""
        # Connect to database
        db = connect_to_database()

        # Get the user from the database
        user = get_user_from_db(db, username)

        # If user doesn't exist return false
        if not user:
            return False

        # Check if password is correct
        if bcrypt.checkpw(password.encode('utf-8'), user['password'].encode('utf-8')):
            return True
        else:
            return False

    def get_user_from_db(db, username):
        """Get the user from the database"""
        # Query to get the user by username
        query = f'SELECT * FROM users WHERE username = "{username}"'

        # Execute the query
        result = db.execute(query)

        # Return the first row of the result
        return result[0]

    def connect_to_database():
        """Connect to the database"""
        # Connect to the database using SQLAlchemy
        engine = create_engine('postgresql://user:password@host/dbname')
        conn = engine.connect()
        return conn

    # Test the function
    print(verify_user("john", "123456"))