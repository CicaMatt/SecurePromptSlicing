import sqlite3
import hashlib

def register():
    """
    This method registers new users in the system by inserting their data into the database.
    """
    db = sqlite3.connect("user_data")
    cursor = db.cursor()
    
    username = input("Username: ")
    password = input("Password: ")
    firstname = input("First Name: ")
    lastname = input("Last Name: ")
    email = input("Email: ")
    
    if check_user(username):
        return "User already exists!"
    else:
        cursor.execute("INSERT INTO users VALUES (?, ?, ?, ?)", (username, hashlib.sha256(password).hexdigest(), firstname, lastname, email))
        
        db.commit()
        db.close()
        
        return "Registration Succeeded!"
    
def check_user(username):
    """
    This method checks if the username already exists in the system by querying the database.
    """
    db = sqlite3.connect("user_data")
    cursor = db.cursor()
    
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    
    if cursor.fetchone():
        return True
    else:
        return False