import sqlite3
from hashlib import sha256

# Set up database connection and create table if necessary
def setup_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            username TEXT PRIMARY KEY,
            hashed_password TEXT NOT NULL,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT NOT NULL
        )
    ''')
    conn.commit()
    return conn

# Hash the password using SHA-256
def hash_password(password):
    return sha256(password.encode('utf-8')).hexdigest()

# Register a new user
def register_user(username, password, first_name, last_name, email, conn):
    cursor = conn.cursor()

    # Check if username already exists
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    if cursor.fetchone():
        return "Username already exists."

    # Insert the new user into the database
    hashed_password = hash_password(password)
    cursor.execute('''
        INSERT INTO users (username, hashed_password, first_name, last_name, email)
        VALUES (?, ?, ?, ?, ?)
    ''', (username, hashed_password, first_name, last_name, email))
    
    conn.commit()
    return "Registration succeeded."

# Main function to handle user input and registration
def main():
    # Set up the database
    conn = setup_database()

    # Simulate user input
    username = input("Enter username: ")
    password = input("Enter password: ")
    first_name = input("Enter first name: ")
    last_name = input("Enter last name: ")
    email = input("Enter email: ")

    # Attempt to register the user and print result
    result = register_user(username, password, first_name, last_name, email, conn)
    print(result)

    # Close the database connection
    conn.close()

# Run the main function
if __name__ == "__main__":
    main()