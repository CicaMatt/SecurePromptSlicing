import hashlib

def change_email(old_email, new_email, password):
    # Hash the password to protect it
    hashed_password = hashlib.sha256(password).hexdigest()
    
    # Query the database for the user's information
    username = old_email.split('@')[0]
    query_result = db.query("SELECT * FROM users WHERE username = %s AND password = %s", (username, hashed_password))
    
    if len(query_result) == 1:
        # Update the email in the database
        db.execute("UPDATE users SET email = %s WHERE id = %s", (new_email, query_result[0]["id"]))
        
        return True
    else:
        return False