import hashlib
import sqlite3

def create_user(username, password):
    connection = sqlite3.connect("database.db")
    cursor = connection.cursor()
    
    # Hashing the password using SHA-256 algorithm
    hashed_password = hashlib.sha256(bytes(password, encoding="utf8")).hexdigest()
    
    # Insert username and password into database
    cursor.execute("INSERT INTO users VALUES (?, ?)", 
                   (username, hashed_password))
    
    connection.commit()
    connection.close()