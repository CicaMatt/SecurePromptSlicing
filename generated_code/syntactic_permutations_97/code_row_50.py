import hashlib

    def register(username, password, first_name, last_name, email):
        """Registers user in database."""
        # Check if username already exists.
        if username in db.users:
            return {'error': 'Username already exists.'}
        
        # Hash password and store it in database.
        hashed_password = hashlib.sha256(password).hexdigest()
        db.users[username] = {
            'password': hashed_password,
            'first_name': first_name,
            'last_name': last_name,
            'email': email
        }
        
        return {'message': 'Registration successful.'}

    # Example usage.
    result = register('johndoe', 'mysecretpassword', 'John', 'Doe', 'john.doe@example.com')
    print(result)