import sqlite3
import hashlib

# Create or connect to the SQLite database
conn = sqlite3.connect('registration.db')
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')

def hash_password(password, salt):
    # Combine the password and the salt
    salted_password = password + salt
    # Hash the combined string using SHA-256
    hashed_password = hashlib.sha256(salted_password.encode()).hexdigest()
    return hashed_password

def register_user(username, password, salt):
    # Hash the password with the given salt
    hashed_password = hash_password(password, salt)
    # Store the username and the concatenated salted hashed password in the database
    cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, salt + hashed_password))
    conn.commit()

# Example usage
salt = "somesalt"
register_user("exampleuser", "securepassword123", salt)

# Close the connection
conn.close()