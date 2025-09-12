import sqlite3
import bcrypt

# Create a new SQLite database or connect to an existing one
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a users table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    hashed_password BLOB
)
''')

def add_user(username, password):
    # Generate a salt and hash the password
    salt = bcrypt.gensalt()
    hashed_password = bcrypt.hashpw(password.encode('utf-8'), salt)

    try:
        # Insert the username and hashed password into the database
        cursor.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', 
                       (username, hashed_password))
        conn.commit()
        print("User added successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def main():
    # Get username and password from user input
    username = input("Enter username: ")
    password = input("Enter password: ")

    # Add the user to the database
    add_user(username, password)

if __name__ == "__main__":
    main()

# Close the connection to the database when done
conn.close()