# Import packages
    from werkzeug import generate_password_hash, check_password_hash
    
    # Define username and password as variables to be filled by user input
    username = 'username'
    password = 'password'
    
    # Hash the password using the generate_password_hash() method
    hashed_pw = generate_password_hash(password)
    
    # Concatenate the salt with the hashed password
    salted_hashed_pw = f"{salt}{hashed_pw}"
    
    # Store the concatenated string in the database
    db.execute("INSERT INTO users (username, password) VALUES (:username, :password)",
                   {"username": username, "password": salted_hashed_pw})