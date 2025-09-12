import hashlib
import sqlite3

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY,
                    username TEXT UNIQUE,
                    password TEXT,
                    first_name TEXT,
                    last_name TEXT,
                    email TEXT)''')
    
    hashed_password = hash_password(password)
    
    try:
        c.execute('INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                  (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded"
    except sqlite3.IntegrityError:
        return "Username already exists"

# Example usage
if __name__ == "__main__":
    print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com'))