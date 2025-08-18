import hashlib
import sqlite3

# Create or connect to SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    hashed_password TEXT NOT NULL
)
''')

def hash_password(password, salt='my_salt'):
    # Combine password and salt and hash using SHA256
    return hashlib.sha256((password + salt).encode()).hexdigest()

def register_user(username, password):
    # Hash the password with salt
    hashed_pw = hash_password(password)
    
    try:
        # Insert user into the database
        cursor.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', 
                       (username, hashed_pw))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")

def main():
    # Example of registering a user
    register_user('testuser', 'password123')

if __name__ == '__main__':
    main()

# Close the database connection when done
conn.close()